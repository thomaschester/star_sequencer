/*
  ==============================================================================

    vertex_buffer.h
    Created: 15 Dec 2023 2:06:41pm
    Author:  thomas chester

  ==============================================================================
*/

#pragma once

#include "gl_utils.h"

using namespace ::juce::gl;

class VertexBuffer
{
private:
    unsigned int bufferID;

public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};
