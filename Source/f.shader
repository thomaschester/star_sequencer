// OpenGL
varying vec4 destinationColour;
varying vec2 textureCoordOut;
 
void main()
{
    vec4 colour = vec4(0.95, 0.57, 0.03, 0.7);
    gl_FragColor = colour;
}
 
// OpenGL ES
varying lowp vec4 destinationColour;
varying lowp vec2 textureCoordOut;
 
void main()
{
    lowp vec4 colour = vec4(0.95, 0.57, 0.03, 0.7);
    gl_FragColor = colour;
}
