#include "instanced.h"

#include "layer.h"

#include <glm/gtc/type_ptr.hpp>

namespace ps
{
namespace drawable
{
namespace renderer
{
Instanced::Instanced(Shader* shader, glm::mat4 transform)
    : Drawable(shader)
    , m_tranform(transform)
{
    shader->bind();

    int position = shader->getAttribLocation("position");
    if(position >= 0)
    {
        m_vbo.useVertexAttrib(static_cast<uint32_t>(position), 3, GL_FLOAT, false, sizeof(VertexComponent), offsetof(VertexComponent, pos));
    }

    int color = shader->getAttribLocation("color");
    if(color >= 0)
    {
        m_vbo.useVertexAttrib(static_cast<uint32_t>(color), 4, GL_FLOAT, false, sizeof(VertexComponent), offsetof(VertexComponent, color));
    }

    int uv = shader->getAttribLocation("uv");
    if(uv >= 0)
    {
        m_vbo.useVertexAttrib(static_cast<uint32_t>(uv), 3, GL_FLOAT, false, sizeof(VertexComponent), offsetof(VertexComponent, uv));
    }

    int normal = shader->getAttribLocation("normal");
    if(normal >= 0)
    {
        m_vbo.useVertexAttrib(static_cast<uint32_t>(normal), 3, GL_FLOAT, false, sizeof(VertexComponent), offsetof(VertexComponent, normal));
    }

    int model = shader->getAttribLocation("model");
    if(model >= 0)
    {
        m_vboTransforms.useVertexAttrib(static_cast<uint32_t>(model + 0), 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), 0 * sizeof(glm::vec4), true);
        m_vboTransforms.useVertexAttrib(static_cast<uint32_t>(model + 1), 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), 1 * sizeof(glm::vec4), true);
        m_vboTransforms.useVertexAttrib(static_cast<uint32_t>(model + 2), 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), 2 * sizeof(glm::vec4), true);
        m_vboTransforms.useVertexAttrib(static_cast<uint32_t>(model + 3), 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), 3 * sizeof(glm::vec4), true);

        m_vboTransforms.useVertexAttribDivisor(static_cast<uint32_t>(model + 0));
        m_vboTransforms.useVertexAttribDivisor(static_cast<uint32_t>(model + 1));
        m_vboTransforms.useVertexAttribDivisor(static_cast<uint32_t>(model + 2));
        m_vboTransforms.useVertexAttribDivisor(static_cast<uint32_t>(model + 3));
    }
}

void Instanced::submit(const int& numVerts, VertexComponent* vertices, const int& numIndices, GLint* indices)
{
    m_changed = true; // nb: Not thread-safe

    //Copy over indices
    int startingIndex = static_cast<int>(m_vertices.size());
    for(int i=0; i<numIndices; ++i)
    {
        m_indices.push_back(indices[i] + startingIndex);
    }

    //Copy over vertices
    for(int i=0; i<numVerts; ++i)
    {
        m_vertices.push_back(vertices[i]);
    }
}

bool Instanced::submit(DrawableEntity* object)
{
    auto objectTexture = object->getTexture();
    if(objectTexture)
    {
        m_textures.clear();
        m_textures.push_back(objectTexture->texture);
        object->setTextureId(static_cast<int>(m_textures.size()) - 1);
    }

    m_objects.clear();
    m_vertices.clear();
    m_indices.clear();
    m_objects.push_back(std::make_pair(object, m_vertices.size()));
    submit(object->numVerts(), object->verts(), object->numIndices(), object->indices());

    m_changed = true;

    //Update Lambda (Refactor maybe??)
    auto fn = [this, object](){
        for(size_t i=0; i<m_objects.size(); i++)
        {
            if(m_objects[i].first == object)
            {
                for(size_t j=0; j<static_cast<size_t>(object->numVerts()); j++)
                {
                    m_vertices[m_objects[i].second + j] = object->verts()[j];
                }
                m_changed = true;
                break;
            }
        }
    };
    object->setUpdateFunc(fn);
    return true;
}

void Instanced::draw(glm::mat4 transform)
{
    if(m_shader != nullptr)
    {
        //m_shader->bind();
        m_shader->setUniform("transform", transform * m_transform);
    }

    std::vector<int> data;
    data.push_back(0);
    for(size_t i = 0; i<m_textures.size(); i++)
    {
        data.push_back(static_cast<int>(i) + 1);
        m_textures[i]->bind(static_cast<uint32_t>(i) + 1);
    }

    if(m_shader != nullptr && data.size() > 0)
    {
        m_shader->setUniform("textures", static_cast<int>(data.size()), &data.front());
    }

    if(m_changed)
    {
        m_ibo.buffer(static_cast<long>(m_indices.size() * sizeof(GLint)), reinterpret_cast<void*>(&m_indices.front()));
        m_vbo.buffer(static_cast<long>(m_vertices.size() * sizeof(VertexComponent)), reinterpret_cast<void*>(&m_vertices.front()));
        m_vboTransforms.buffer(static_cast<long>(m_transforms.size() * sizeof(glm::mat4)), &m_transforms.front());
        m_changed = false;
    }

    m_ibo.bind();
    m_vbo.bind();
    m_vboTransforms.bind();

    glDrawElementsInstanced(m_drawType, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr, static_cast<int>(m_transforms.size()));
}

void Instanced::submit(const glm::mat4& transform)
{
    m_transforms.push_back(transform);
    m_changed = true;
}

}
}
}
