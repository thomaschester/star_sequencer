/*
  ==============================================================================

    index_buffer.h
    Created: 15 Dec 2023 2:05:53pm
    Author:  thomas chester

  ==============================================================================
*/

#pragma once

#include "gl_utils.h"

using namespace ::juce::gl;

class IndexBuffer
{
private:
    unsigned int bufferID;
    unsigned int count;

public:
    IndexBuffer(const unsigned int *data, unsigned int _count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getCount() const { return count; };
};
