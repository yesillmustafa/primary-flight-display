#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include<string>
#include <GLES2/gl2.h>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
   
    void attachShader(const char* fileName,unsigned int shaderType);

    void link();

    void use();
    GLuint getProgramId();

private:
    std::string getShaderFromFile(const char* fileName);
    GLuint m_ProgramId;
  
};


#endif