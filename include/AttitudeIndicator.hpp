#ifndef AI_HPP
#define AI_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class AttitudeIndicator {
public:
    AttitudeIndicator();
    void Draw(float circleYPositions, float circleRotations);
private:
    ShaderProgram program;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint arcVertexBuffer;
    GLuint arcIndexBuffer;
};

#endif // AI_HPP
