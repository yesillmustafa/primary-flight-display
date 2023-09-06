#ifndef INDICATOR_HPP
#define INDICATOR_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class Indicator {
public:
    Indicator();
    void Draw();
private:
    void createIndicator1();
    void drawIndicator1();
    void createIndicator2();
    void drawIndicator2();

    ShaderProgram program;
    GLuint vertexBuffer1;
    GLuint indexBuffer1;
    GLuint vertexBuffer2;
    GLuint indexBuffer2;
    int indexCount1;
    int indexCount2;


};

#endif
