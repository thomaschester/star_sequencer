/*
  ==============================================================================

    index_buffer.cpp
    Created: 15 Dec 2023 2:05:53pm
    Author:  thomas chester

  ==============================================================================
*/

#include "index_buffer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int _count)
    : count(_count)
{
    GLCall(glGenBuffers(1, &bufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &bufferID));
}

void IndexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
}
void IndexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
