#ifndef UI_HPP
#define UI_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class UserInterface {
public:
    UserInterface();
    void Draw();
private:
    ShaderProgram program;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint uiTex;
};

#endif 