#include "model.h"

#include <fstream>

namespace ps
{
namespace
{
std::vector<std::string> split(const std::string& s, char seperator)
{
    std::vector<std::string> output;
    std::string::size_type prev_pos = 0, pos = 0;
    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );
        output.push_back(substring);
        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos));
    return output;
}
}

namespace drawable
{
Model::Model(const std::string& context, const std::string& path, Shader* shader)
    : DrawableEntity(context, shader)
    , m_path(path)
{
    loadModel();
}

void Model::loadModel()
{
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> uv;
    std::vector<VertexComponent> vertices;

    std::ifstream ifs(m_path);
    if (ifs.is_open())
    {
        std::string line;
        while ( getline (ifs, line) )
        {
            std::vector<std::string> ls = split(line, ' ');
            if(ls.size() > 3 && ls.front().compare("v") == 0)
            {
                VertexComponent v;
                v.pos = glm::vec3(stof(ls[1]), stof(ls[2]), stof(ls[3]));
                vertices.push_back(v);
            }
            else if(ls.size() > 3 && ls.front().compare("vn") == 0)
            {
                normals.emplace_back(stof(ls[1]), stof(ls[2]), stof(ls[3]));
            }
            else if(ls.size() > 2 && ls.front().compare("vt") == 0)
            {
                uv.emplace_back(stof(ls[1]), stof(ls[2]), 0);
            }
            else if(ls.size() > 3 && ls.front().compare("f") == 0)
            {
                auto vertInfo1 = split(ls[1], '/');
                auto vertInfo2 = split(ls[2], '/');
                auto vertInfo3 = split(ls[3], '/');

                int vertex1 = stoi(vertInfo1[0]) -1;
                int vertex2 = stoi(vertInfo2[0]) -1;
                int vertex3 = stoi(vertInfo3[0]) -1;

                //TODO: Refactor this to reuse vertices when possible.
                // Currently, recreating a new vertex for each indice
                // which ultimately causes issues with lighting (normals)
                // and general performance (although minor)

                VertexComponent v1 = vertices[static_cast<size_t>(vertex1)];
                VertexComponent v2 = vertices[static_cast<size_t>(vertex2)];
                VertexComponent v3 = vertices[static_cast<size_t>(vertex3)];

                //Tex Coords
                if(vertInfo1.size() > 1 && strcmp(vertInfo1[1].c_str(), "") != 0 && uv.size() > 0)
                {
                    v1.uv = uv[static_cast<size_t>(stoi(vertInfo1[1]))-1];
                    v2.uv = uv[static_cast<size_t>(stoi(vertInfo2[1]))-1];
                    v3.uv = uv[static_cast<size_t>(stoi(vertInfo3[1]))-1];
                }

                //Normals
                if(vertInfo1.size() > 2 && strcmp(vertInfo1[2].c_str(), "") != 0 && normals.size() > 0)
                {
                    v1.normal = normals[static_cast<size_t>(stoi(vertInfo1[2]))-1];
                    v2.normal = normals[static_cast<size_t>(stoi(vertInfo2[2]))-1];
                    v3.normal = normals[static_cast<size_t>(stoi(vertInfo3[2]))-1];
                }

                if(vertInfo1.size() > 0)
                {
                    addVertex(v1);
                    vertex1 = static_cast<int>(numVerts() - 1);

                    addVertex(v2);
                    vertex2 = static_cast<int>(numVerts() - 1);

                    addVertex(v3);
                    vertex3 = static_cast<int>(numVerts() - 1);

                    m_indices.push_back(vertex1);
                    m_indices.push_back(vertex2);
                    m_indices.push_back(vertex3);
                }
            }
            else
            {
                //Not handling yet
            }
        }
        ifs.close();
    }
    else
    {
        //Failed to open
    }
}
}
}
