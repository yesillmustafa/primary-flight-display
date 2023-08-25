#include "UserInterface.hpp"
#include <GLES2/gl2.h>
#include <iostream>
#include "TextureManager.hpp"


UserInterface::UserInterface() {
    //shaders just include texture
    program.attachShader("../shaders/vs-usetexture.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-usetexture.glsl", GL_FRAGMENT_SHADER);
    program.link();


 GLfloat uivertices[] = {
    // Position (X, Y, Z)    Texture Coordinates (S, T)
    1.0f,  1.0f, 0.0f,     0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,    1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,     0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f,    1.0f, 1.0f,
};

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uivertices), uivertices, GL_STATIC_DRAW);


GLuint uiindices[] = {
    0, 1, 2, // First triangle
    1, 2, 3  // Second triangle
};



    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uiindices), uiindices, GL_STATIC_DRAW);

    //load texture
    uiTex = TextureManager::getInstance()->loadTexture("../images/ui_layer.png");

}

void UserInterface::Draw() {
    program.use();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
   
    // Get attribute and uniform locations
    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "a_position");
    GLint texCoordAttrib = glGetAttribLocation(program.getProgramId(), "texCoord");

    
    GLint textureUniform = glGetUniformLocation(program.getProgramId(), "textureSampler");
    
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(texCoordAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glUniform1i(textureUniform, 0); // Assuming texture unit 0
   
    //activate texture
    TextureManager::getInstance()->activateTexture(GL_TEXTURE0,uiTex);

    glDrawElements(GL_TRIANGLES,12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
    glDisableVertexAttribArray(texCoordAttrib);
    glUseProgram(0);
}
