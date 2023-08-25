#ifndef SPEEDINDICATOR_HPP
#define SPEEDINDICATOR_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class SpeedIndicator {
public:
    SpeedIndicator();
    void Draw(float yoffset);
private:
    ShaderProgram program;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint siTex;

};

#endif 