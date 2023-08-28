#ifndef VERTICALSPEEDINDIS_HPP
#define VERTICALSPEEDINDIS_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class VSpeed {
public:
    VSpeed();
    void Draw_indicator(float yoffset);
    void creatIndicator();
private:
    ShaderProgram program;
    GLuint vertexBuffer_ind;
    GLuint indexBuffer_ind;

};

#endif 