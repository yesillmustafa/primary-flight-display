#version 100
attribute vec3 a_position;
attribute vec2 texCoord;
varying vec2 fragTexCoord;

void main() {
    gl_Position = vec4(a_position, 1.0);
    fragTexCoord = texCoord;
}
