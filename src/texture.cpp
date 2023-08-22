#include <GLES2/gl2.h>
#include <EGL/egl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <GLFW/glfw3.h>
class texture

{
private:
    
public:
    
    GLuint settextureinner();
    GLuint settextureouter();
};


GLuint texture::settextureinner()
{

        GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Replace this with your own texture loading code using stb_image.h
    int width, height, numChannels;
    unsigned char* data = stbi_load("./images/texture.png", &width, &height, &numChannels, 0);
   std::cout<<data<<std::endl;
    if (data)
    {
        GLenum format = GL_RGB;
        if (numChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
        glfwTerminate();
        exit(1);
    }
    return texture;
}
GLuint texture::settextureouter()
{

        GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Replace this with your own texture loading code using stb_image.h
    int width, height, numChannels;
    unsigned char* data = stbi_load("altimeter.png", &width, &height, &numChannels, 0);
   
    if (data)
    {
        GLenum format = GL_RGB;
        if (numChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
        glfwTerminate();
        exit(1);
    }
    return texture;
}