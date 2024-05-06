#include "MainComponent.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

/* TODO: what's left after 02/05/24 work ☐ ☑


 ☐ VertexBuffer array with star position data does not exist yet. Right now it should be a float array of x, y, and z positions
        ☐ Later will want to add and test pointSize and color
    ☐ Remove index buffer stuff because I think it's unnecessary for this application (no overlapping vertex positions)
    ☐ For MVP, add glPointSize(pointSize) and pick a point size after researching a little to see a realistic float to use.
        Later it will just be set individually per star in the vertex buffer
    ☑ Build error and I don't know why "8 duplicate symbols for architecture x86_64" from just trying to build with the new header files
        Might be a projucer thing?
    ☐ Figure out star count and create a fixed size array as a member of this class to add to for the vertex buffer data
    ☐ If the globe projects, focus on a big code clean-up/refactor before starting to add more stuff
*/

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize(850, 850);

    // Init star stuff
    // TODO: fix absolute path
    std::ifstream input("/Users/thom/code/star_sequencer/Source/hip_main.dat");
    if (!input.is_open())
    {
        std::cerr << "Error opening file: " << std::strerror(errno) << std::endl;
        return;
    }
    starManager.addStars(input);
    input.close();

    // Init openGL context stuff
    openGLContext.setOpenGLVersionRequired(juce::OpenGLContext::OpenGLVersion::openGL4_1);
    openGLContext.setComponentPaintingEnabled(true);
}

MainComponent::~MainComponent()
{
    shutdownOpenGL();
}

//==============================================================================
void MainComponent::initialise()
{
    // Initialise GL objects for rendering here.

    jassert(juce::OpenGLHelpers::isContextActive());
    //    context.setContinuousRepainting (true);
    GLCall(glEnable(GL_PROGRAM_POINT_SIZE));

    shader = std::make_unique<juce::OpenGLShaderProgram>(openGLContext);

    std::cout << shader->getLastError() << std::endl;

    // Init shader stuff
    // TODO: load shaders from files
    // TODO: add color and point size here after initial test of position
    //        "layout(location = 1) in float pointSize;\n"
    //        "layout(location = 2) in vec4 color;\n"
    //
    juce::String vertexShader = R"(
        #version 330 core
        layout(location = 0) in vec4 position;
        layout(location = 1) in float size;
        layout(location = 2) in vec4 color;
        
        out vec4 v_Color;
        
        uniform mat4 u_MVP;

        void main() {
            gl_PointSize = size;
            gl_Position = u_MVP * position;
            v_Color = color;
        })";

    juce::String fragmentShader = R"(
        #version 330 core
        layout(location = 0) out vec4 color;
        
        in vec4 v_Color;
        
        void main() {
           color = v_Color;
        })";

    shader->addVertexShader(vertexShader);
    std::cout << shader->getLastError() << std::endl;
    shader->addFragmentShader(fragmentShader);
    std::cout << shader->getLastError() << std::endl;
    shader->link();

    u_MVP = std::make_unique<juce::OpenGLShaderProgram::Uniform>(*shader, "u_MVP");

    std::cout << shader->getLastError() << std::endl;

    int count = 0;
    // TODO: this is where the vertex buffer data will be created and loaded
    for (const auto &[name, star] : starManager.getStars())
    {
        vertexBufferData[count++] = star->getXCoord();
        vertexBufferData[count++] = star->getYCoord();
        vertexBufferData[count++] = star->getZCoord();
        vertexBufferData[count++] = star->getMarkerSize();
        vertexBufferData[count++] = star->getColor().getFloatRed();
        vertexBufferData[count++] = star->getColor().getFloatGreen();
        vertexBufferData[count++] = star->getColor().getFloatBlue();
        vertexBufferData[count++] = 1.0f; // Alpha
    }

    //    std::cout << "count is " << count << std::endl;

    // Vertex array stuff
    vertexArray = std::make_unique<VertexArray>();
    vertexBuffer = std::make_unique<VertexBuffer>(vertexBufferData, sizeof(vertexBufferData));

    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(1);
    layout.push<float>(4);

    vertexArray->addBuffer(*vertexBuffer, layout);
}

void MainComponent::shutdown()
{
    shader.reset();
    vertexArray.reset();
    vertexBuffer.reset();

    openGLContext.detach();
}

void MainComponent::render()
{
    jassert(juce::OpenGLHelpers::isContextActive());

    GLCall(glGetError());

    // This clears the context with a black background.

    vertexArray->bind();

    auto desktopScale = (float)openGLContext.getRenderingScale();
    juce::OpenGLHelpers::clear(juce::Colour::fromRGB(17, 20, 33));

    //    glEnable (GL_BLEND);
    //    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0,
               0,
               juce::roundToInt(desktopScale * (float)getWidth()),
               juce::roundToInt(desktopScale * (float)getHeight()));

    shader->use();

    // Set Camera at the origin
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f); // Looking along the -Z axis
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);            // Y is up!

    // Create view matrix
    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, up);

    // Create a perspective projection matrix
    float fov = glm::radians(45.0f); // or whatever is appropriate for your circle
    float aspectRatio = 1.0f;        // Depends on your window size
    float nearPlane = 0.1f;          // Typically a small number
    float farPlane = 100.0f;         // Typically a large number
    glm::mat4 projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

    // TODO:
    // Something is fucked up here. The sides look distorted in an offset way during rotation
    auto rotationMatrix = (juce::Matrix3D<float>(&projection[0][0])).rotation({-0.3f, 5.0f * std::sin((float)getFrameCounter() * 0.001f), 0.0f});

    // Scale down the projection
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 finalProjection = scaleMatrix * projection; // Apply scaling

    glm::mat4 _finalValue = finalProjection * view;

    juce::Matrix3D<float> finalValue = juce::Matrix3D<float>(&_finalValue[0][0]) * rotationMatrix;

    // In your render function:
    u_MVP->setMatrix4(finalValue.mat, 1, GL_FALSE);

    // Set the identity matrix for the uniform
    //    u_MVP->setMatrix4(proj.mat, 1, GL_FALSE);

    //    GLCall(glPointSize(4.0f));
    GLCall(glDrawArrays(GL_POINTS, 0, 2724));
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g)
{
    // You can add your *component specific* drawing code here!
    // This will draw over the top of the openGL background.
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
