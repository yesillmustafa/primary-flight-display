#include "altimeter.hpp"
#include <GLES2/gl2.h>
#include <iostream>
#include "TextureManager.hpp"


Altimeter::Altimeter() {
    //shaders just include texture
    program.attachShader("../shaders/vs-usetexture.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-usetexture.glsl", GL_FRAGMENT_SHADER);
    program.link();

    GLfloat vertices[] = {
        // Position (X, Y, Z)    Texture Coordinates (S, T)

        0.775f,  0.875f, 0.0f,     1.0f, -0.1f,
        0.575f, 0.875f, 0.0f,     0.0f, -0.1f,
        0.775f, -0.125f, 0.0f,     1.0f, 0.00000000001f,
        0.575f, -0.125f, 0.0f,     0.0f, 0.00000000001f, //vs allows bigger or lower than 0.0

    };




    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint indices[] = {
        0, 1, 2, // İlk üçgen
        1, 2, 3, // İkinci üçgen
        4, 5, 6, // Üçüncü üçgen
        5, 6, 7  // Dördüncü üçgen
    };



    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //load texture
    altimeterTex = TextureManager::getInstance()->loadTexture("../images/altimeter.jpg");

}

void Altimeter::Draw(float yoffset) {
    program.use();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "a_position");
    GLint texCoordAttrib = glGetAttribLocation(program.getProgramId(), "texCoordy");
    GLint yoffsetloc = glGetUniformLocation(program.getProgramId(), "modelYOffset");
    GLint textureUniform = glGetUniformLocation(program.getProgramId(), "textureSampler");

    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(texCoordAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glUniform1f(yoffsetloc, yoffset);
    glUniform1i(textureUniform, 1); // Assuming texture unit 0

    //activate texture
    TextureManager::getInstance()->activateTexture(GL_TEXTURE1,altimeterTex);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
    glDisableVertexAttribArray(texCoordAttrib);

    glUseProgram(0);
}
