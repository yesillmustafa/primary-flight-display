#ifndef LANDSCAPE_HPP
#define LANDSCAPE_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class Landscape {
public:
    Landscape();
    void Draw(float circleYPositions, float circleRotations);

private:
    ShaderProgram program;
    GLuint vertexBuffer;
    GLuint indexBuffer;
};

#endif // LANDSCAPE_HPP
