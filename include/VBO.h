#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<GLFW/glfw3.h>
#include<GLES2/gl2.h>


class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();

	void LinkAttrib(VBO& VBO, GLint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
};

#endif