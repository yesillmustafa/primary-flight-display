#ifndef ALTIMETER_HPP
#define ALTIMETER_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class Altimeter {
public:
    Altimeter();
    void Draw(float yoffset);
    void Draw_ui();
private:
    ShaderProgram program;
    GLuint vertexBuffer;
    GLuint indexBuffer;
     GLuint vertexBuffer_ui;
    GLuint indexBuffer_ui;
    GLuint textureid;
    GLuint textureid_ui;
    GLuint texCoordBuffer;
};

#endif 