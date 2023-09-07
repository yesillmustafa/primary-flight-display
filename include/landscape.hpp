#ifndef LANDSCAPE_HPP
#define LANDSCAPE_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"
#include <vector>

class Landscape {
public:
    Landscape();
    void Draw(float circleYPositions, float circleRotations);

private:

    void createLines();
    void createLandscape();
    void drawLines(float circleYPositions, float circleRotations);
    void drawLandscape(float circleYPositions, float circleRotations);


    ShaderProgram program;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint lines_VertexBuffer;
    GLuint lines_IndexBuffer;
    GLuint lines_IndexCount;
};

#endif // LANDSCAPE_HPP
