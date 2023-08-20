#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class Aircraft {
public:
    Aircraft();
    void Draw();
private:
    ShaderProgram program;
    GLuint vertexBuffer;
    GLuint indexBuffer;
};

#endif // AIRCRAFT_HPP
