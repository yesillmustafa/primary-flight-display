#ifndef HEADINGINDICATOR_HPP
#define HEADINGINDICATOR_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class HeadingIndicator {
public:
    HeadingIndicator();
    void Draw(float circleRotations);
private:
    ShaderProgram program;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint indexCount;
    GLuint hiTex;

};

#endif 