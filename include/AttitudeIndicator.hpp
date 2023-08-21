#ifndef AI_HPP
#define AI_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class AttitudeIndicator {
public:
    AttitudeIndicator();
    void Draw(float circleYPositions, float circleRotations);
private:

    void createHorizontalLines();
    void createArcScaleLines();
    void createArc();
    void createArcTriangle();

    ShaderProgram program;

    GLuint horizontalLines_VertexBuffer;
    GLuint horizontalLines_IndexBuffer;
    GLuint horizontalLines_IndexCount;

    GLuint arcScaleLines_VertexBuffer;
    GLuint arcScaleLines_IndexBuffer;
    GLuint arcScaleLines_IndexCount;

    GLuint arc_VertexBuffer;
    GLuint arc_IndexBuffer;
    GLuint arc_IndexCount;

    GLuint arcTriangle_VertexBuffer;
    GLuint arcTriangle_IndexBuffer;
    GLuint arcTriangle_IndexCount;
};

#endif // AI_HPP
