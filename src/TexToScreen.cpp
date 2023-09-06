#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>
#include "TexToScreen.hpp"
#include "Texture.h"
#include "characters.hpp"
#include "EBO.h"
#include "VBO.h"
#include "shaderClass.h"

    GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,        0.0f, 1.0f,   // Sol alt köşe// Lower left corner
-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,        0.0f, 0.0f, // Sol üst köşe // Upper left corner
 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,        1.0f, 0.0f,   // Sağ üst köşe// Upper right corner
 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,        1.0f, 1.0f // Sağ alt köşe // Lower right corner
/*Tex Coordların konumlanması önemli victorun ki stbye uyarlamak için texkoordlar ters konumlanmış*/
};
/*TEX COORD
0.0f, 1.0f,
0.0f, 0.0f,
1.0f, 0.0f,
1.0f, 1.0f  
*/

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};
Shader shaderProgram("vs-default.glsl", "fs-default.glsl");
	
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	

	EBO EBO1(indices, sizeof(indices));

void tex::CreateResources() {


indicesSize=indices;
 chr character;

	

    GLint aPos = glGetAttribLocation(shaderProgram.ID,"aPos");
	
	VBO1.LinkAttrib(VBO1, aPos, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	

	GLint aColor = glGetAttribLocation(shaderProgram.ID,"aColor");
	VBO1.LinkAttrib(VBO1, aColor, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	

    GLint aTex = glGetAttribLocation(shaderProgram.ID,"aTex");
	
	VBO1.LinkAttrib(VBO1, aTex, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    

    // Unbind the buffer and shader program after setting up attributes
    VBO1.Unbind();
	EBO1.Unbind();
    

    
    Texture opengles(NULL,32*14/*Bu 14 girilecek olan stringin uzunluğunu belirtiyor*/,32,GL_TEXTURE_2D, GL_TEXTURE0, GL_LUMINANCE, GL_UNSIGNED_BYTE);
    opengles20=opengles;
    glBindTexture(GL_TEXTURE_2D, opengles20.ID);

 
Texture opengles20(NULL,32*14/*Bu 14 girilecek olan stringin uzunluğunu belirtiyor*/,32,GL_TEXTURE_2D, GL_TEXTURE0, GL_LUMINANCE, GL_UNSIGNED_BYTE);
//Boş bir texture nesnesi oluşturuyoruz

//karakterlerin hepsi 32x32 büyüklüğünde
opengles20.texUnit(shaderProgram, "tex0", 0);

glBindTexture(GL_TEXTURE_2D,opengles20.ID);

glBindTexture(GL_TEXTURE_2D,opengles20.ID);
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*0, 0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(0));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*1, 0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(2));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*2, 0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(2));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*3, 0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(3));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*4, 0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(2));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*5, 0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(0));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*6, 0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(0));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*7, 0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(0));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*8, 0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(0));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*9, 0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(0));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*10,0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(0));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*11,0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(0));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*12,0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(0));
glTexSubImage2D(GL_TEXTURE_2D,0      ,32*13,0	,32,32,GL_LUMINANCE,GL_UNSIGNED_BYTE,character.get(0));


   
}

void tex::DrawScene() {

   shaderProgram.Activate();
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "scale"), 0.25f);
	glActiveTexture(GL_TEXTURE0);
	opengles20.Bind();
	VBO1.Bind();
    glBindBuffer(GL_ARRAY_BUFFER, VBO1.ID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indicesSize);
	
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
