#version 100
attribute vec3 position;
uniform mat4 model;
void main()
{
    gl_Position = model * vec4(position, 1.0);
}
