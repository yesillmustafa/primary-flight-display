#ifndef ALTIMETER_HPP
#define ALTIMETER_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class Altimeter {
public:
    Altimeter();
    void Draw();
private:
    ShaderProgram program;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint textureid;
    GLuint texCoordBuffer;
};

#endif 