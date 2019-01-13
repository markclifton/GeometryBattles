#include "vertexbuffer.h"

namespace ps
{
namespace buffers
{
VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_vbo);
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    enableVertexAttribs();
}

void VertexBuffer::buffer(const long& totalSize, void* data, const unsigned int& drawType)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, totalSize, data, drawType);

    enableVertexAttribs();
}

void VertexBuffer::enableVertexAttribs()
{
    for(auto& attrib : m_vertexAttribs)
    {
        glEnableVertexAttribArray(attrib.vertexPosition);
        glVertexAttribPointer(attrib.vertexPosition, attrib.count, attrib.type, attrib.normalized, attrib.stride, reinterpret_cast<GLvoid*>(attrib.offset));

        if(attrib.instanced)
        {
            glVertexAttribDivisor(attrib.vertexPosition, 1);
        }
    }

    for(auto& divisor : m_vertexAttribDivisors)
    {
        glVertexAttribDivisor(divisor, 1);
    }
}

void VertexBuffer::useVertexAttrib(uint32_t vertexPosition, int count, uint32_t type, bool normalized, int stride, size_t offset, bool instanced)
{
    // Update if exist
    for(auto& attrib : m_vertexAttribs)
    {
        if(attrib.vertexPosition == vertexPosition)
        {
            attrib.count = count;
            attrib.type = type;
            attrib.normalized = normalized;
            attrib.stride = stride;
            attrib.offset = offset;
            attrib.instanced = instanced;
            return;
        }
    }

    VertexAttrib va;
    va.vertexPosition = vertexPosition;
    va.count = count;
    va.type = type;
    va.normalized = normalized;
    va.stride = stride;
    va.offset = offset;
    va.instanced = instanced;

    m_vertexAttribs.push_back(va);
}

void VertexBuffer::useVertexAttribDivisor(uint32_t vertexPosition)
{
    m_vertexAttribDivisors.push_back(vertexPosition);
}

}
}
