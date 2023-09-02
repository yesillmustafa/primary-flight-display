#version 100
attribute vec3 position;
uniform float modelYOffset; // Uniform to control Y-axis offset
void main()
{
    if(position.y<0.400001)
    {  gl_Position = vec4(position.x, position.y + 0.0, position.z, 1.0);}
    else
    {
          gl_Position = vec4(position.x, position.y + modelYOffset, position.z, 1.0);
    }
}
