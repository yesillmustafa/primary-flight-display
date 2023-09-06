#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<GLFW/glfw3.h>
#include<GLES2/gl2.h>
#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const GLvoid *bytes,GLsizei width,GLsizei height,GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};
#endif