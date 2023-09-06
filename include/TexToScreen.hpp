#include "Texture.h"
#include "shaderProgram.hpp"
#include<GLES2/gl2.h>

class tex{

private:
 GLuint vertexBuffer;
GLuint indexBuffer;
Texture opengles20;
public:
tex():opengles20(NULL,32*14/*Bu 14 girilecek olan stringin uzunluğunu belirtiyor*/,32,GL_TEXTURE_2D, GL_TEXTURE0, GL_LUMINANCE, GL_UNSIGNED_BYTE){
    CreateResources();
};

ShaderProgram program;

GLuint *indicesSize;
void CreateResources();
void DrawScene();

};