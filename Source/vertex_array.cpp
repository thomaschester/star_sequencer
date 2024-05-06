/*
  ==============================================================================

    vertex_array.cpp
    Created: 15 Dec 2023 2:06:31pm
    Author:  thomas chester

  ==============================================================================
*/

#include "vertex_array.h"
#include "vertex_buffer_layout.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &arrayID));
    GLCall(glBindVertexArray(arrayID));
};

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &arrayID));
};

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(arrayID));
}

void VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    bind();
    vb.bind();
    const auto &elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
};
