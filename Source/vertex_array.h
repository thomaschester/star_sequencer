/*
  ==============================================================================

    vertex_array.h
    Created: 15 Dec 2023 2:06:31pm
    Author:  thomas chester

  ==============================================================================
*/

#pragma once

#include "gl_utils.h"

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

using namespace ::juce::gl;

class VertexArray
{
private:
    unsigned int arrayID;

public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
};
