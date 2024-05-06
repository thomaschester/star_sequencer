/*
  ==============================================================================

    gl_utils.h
    Created: 15 Dec 2023 2:04:53pm
    Author:  thomas chester

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

using namespace ::juce::gl;

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    jassert(GLLogCall(#x, __FILE__, __LINE__));

inline void GLClearError()
{
    while (glGetError())
    {
    };
}

inline bool GLLogCall(const char *function, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "!!! OpenGL Error !!!\nError Code: " << error << " | Function: " << function << " | File: "
                  << file << " | Line: " << line << std::endl;
        return false;
    };
    return true;
}
