#ifndef AI_HPP
#define AI_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class AttitudeIndicator {
public:
    AttitudeIndicator();
    void Draw(float circleYPositions, float circleRotations, float slipskid);
private:

    void createHorizontalLines();
    void createArcScaleLines();
    void createArc();
    void createArcTriangle();
    void createBankAngle();
    void createSlipSkidIndicator();

    void drawHorizontalLines(float circleYPositions, float circleRotations);
    void drawArcScaleLines(float circleYPositions, float circleRotations);
    void drawArc(float circleYPositions, float circleRotations);
    void drawArcTriangle(float circleYPositions, float circleRotations);
    void drawBankAngle(float circleYPositions, float circleRotations);
    void drawSlipSkidIndicator(float circleYPositions, float circleRotations, float slipskid);


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

    GLuint bankAngle_VertexBuffer;
    GLuint bankAngle_IndexBuffer;
    GLuint bankAngle_IndexCount;

    GLuint slipSkid_VertexBuffer;
    GLuint slipSkid_IndexBuffer;
    GLuint slipSkid_IndexCount;
};

#endif // AI_HPP
