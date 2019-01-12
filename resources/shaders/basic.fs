#version 330 core

struct Light
{
    vec3 color;
    float intensity;
};

struct PointLight
{
    Light light;
    vec3 elc;
    vec3 pos_w;
};

struct SpotLight
{
    PointLight plight;
    vec3 direction;
    float cutoff;
};

out vec4 finalColor;

in FSData {
    vec3 pos;
    vec4 color;
    vec3 uv;
    vec3 normal;
    float distance;
} fs;

in mat4 tform;
in vec4 shadowCoords;

uniform sampler2D textures_[16];

uniform int spotlightCount;
uniform SpotLight spotlights[8];

uniform int pointlightCount;
uniform PointLight pointlights[8];

vec4 calculateLight( Light light, vec3 normal, vec3 direction, float distance )
{
    vec3 n = normalize( normal );
    vec3 l = normalize( direction );
    vec3 r = reflect(-l,n);

    float totalColor = 0;

    float diffuseFactor = clamp( dot( normal,l ), 0,1 ) / (distance*distance);
    if(diffuseFactor > 0)
    {
        totalColor += diffuseFactor;

        float specularFactor = clamp( dot( l,r ), 0,1 );
        if( specularFactor > 0)
        {
            totalColor += pow(specularFactor,5) / (distance*distance);
        }
    }

    return vec4( light.color * totalColor, 1.f ) * light.intensity;
}

vec4 calculatePLight(PointLight plight, vec3 normal)
{
    vec3 direction = fs.pos - plight.pos_w;
    float distance = length(direction);

    vec4 color = calculateLight(plight.light, normal, -direction, distance);

    plight.elc.z += 0.0001;
    float attenuation = (plight.elc.x * distance * distance) + (plight.elc.y * distance) + plight.elc.z;
    return color / attenuation;
}

vec4 calculateSpotLight(SpotLight slight, vec3 normal)
{
    vec3 direction = normalize(fs.pos - slight.plight.pos_w);
    float spotFactor = dot(direction, slight.direction);

    vec4 color = vec4(0,0,0,0);
    if( spotFactor > slight.cutoff)
    {
        color = calculatePLight(slight.plight, normal);
        color *= (1.0 - (1.0 - spotFactor) / (1.0 - slight.cutoff));
    }

    return color;
}

void main()
{
    finalColor = fs.color;
    if( fs.uv.z >= 0.f )
    {
        finalColor = texture(textures_[int(fs.uv.z + 1)], fs.uv.xy);
    }

    if(length(fs.normal) > 0)
    {
        Light light;
        light.color = vec3(1,1,1);
        light.intensity = 5.f;

        vec4 totalLight = vec4(.05,.05,.05,1);
        totalLight += calculateLight( light, fs.normal, -fs.pos, fs.distance );

        for(int i=0; i<pointlightCount; i++)
        {
            totalLight += calculatePLight(pointlights[i], fs.normal);
        }

        for(int i=0; i<spotlightCount; i++)
        {
            totalLight += calculateSpotLight(spotlights[i], fs.normal);
        }

        float alpha = finalColor.a;
        finalColor *= totalLight;

        vec2 poissonDisk[4] = vec2[](
          vec2( -0.94201624, -0.39906216 ),
          vec2( 0.94558609, -0.76890725 ),
          vec2( -0.094184101, -0.92938870 ),
          vec2( 0.34495938, 0.29387760 )
        );

        float visibility = 1.0;
        vec3 sh = shadowCoords.xyz / shadowCoords.w;
        if ( texture( textures_[0], sh.xy ).z  <  sh.z - 0.005){
            visibility = 0.75;
        }

        finalColor *= visibility;
        finalColor.a = alpha;
    }
}
