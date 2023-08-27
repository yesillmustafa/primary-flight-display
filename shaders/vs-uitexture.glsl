#version 100
attribute vec3 a_position;
attribute vec2 texCoord;
attribute vec2 texCoordy;
varying vec2 fragTexCoord;
uniform float modelYOffset; // Uniform to control Y-axis offset

void main() {
    gl_Position = vec4(a_position, 1.0);
    
    if (texCoordy.x > 0.0 || texCoordy.x < 0.0 || texCoordy.y > 0.0 || texCoordy.y < 0.0) {
        fragTexCoord = texCoordy + vec2(0.0f, modelYOffset); // Apply offset to Y coordinate
    } else {
        fragTexCoord = texCoord;
    }
}
