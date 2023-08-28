#ifndef VERTICALSPEED_HPP
#define VERTICALSPEED_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class verticalSpeed {
public:
    verticalSpeed();
    void Draw();
    
private:
    ShaderProgram program;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint vertiTex;

};

#endif 