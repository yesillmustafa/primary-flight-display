#include "altimeter.hpp"
#include <GLES2/gl2.h>
#include <iostream>
#include "texture.cpp"


Altimeter::Altimeter() {
    //shaders just include texture
    program.attachShader("../shaders/vs-altimeter.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-altimeter.glsl", GL_FRAGMENT_SHADER);
    program.link();

    float art=0.022;
    GLfloat vertices[] = {
        // Position (X, Y, Z)    Texture Coordinates (S, T)
        0.85f,  0.71f, 0.0f,     1.0f, -1.0f,
        0.57f,  0.71f, 0.0f,     0.0f, -1.0f,
        0.85f, -0.51f, 0.0f,     1.0f, 0.0f,
        0.57f, -0.51f, 0.0f,     0.0f, 0.0f,

        -0.8f-(2*art),  0.7f+art, 0.0f,    -1.0f, -1.0f,
        -0.6f+art,  0.7f+art, 0.0f,    0.0f, -1.0f,
        -0.8f-(2*art), -0.5f-art, 0.0f,    -1.0f, 0.0f,
        -0.6f+art, -0.5f-art, 0.0f,    0.0f, 0.0f,
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
    texture tex;
    textureid=tex.settextureinner();

 GLfloat uivertices[] = {
    // Position (X, Y, Z)    Texture Coordinates (S, T)
    1.0f,  1.0f, 0.0f,     0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,    1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,     0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f,    1.0f, 1.0f,
};





    glGenBuffers(1, &vertexBuffer_ui);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_ui);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uivertices), uivertices, GL_STATIC_DRAW);


GLuint uiindices[] = {
    0, 1, 2, // First triangle
    1, 2, 3  // Second triangle
};



    glGenBuffers(1, &indexBuffer_ui);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_ui);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uiindices), uiindices, GL_STATIC_DRAW);

   
    textureid_ui=tex.settextureouter();


}

void Altimeter::Draw() {
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

    glUniform1i(textureUniform, 1); // Assuming texture unit 0

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureid); // Bind the loaded texture

    glDrawElements(GL_TRIANGLES,12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
    glDisableVertexAttribArray(texCoordAttrib);


    glUseProgram(0);
    
   
}


void Altimeter::Draw_ui(){
     program.use();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_ui);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_ui);

    // Get attribute and uniform locations
   
    // Get attribute and uniform locations
    GLint posAttrib_ui = glGetAttribLocation(program.getProgramId(), "a_position");
    GLint texCoordAttrib_ui = glGetAttribLocation(program.getProgramId(), "texCoord");

    
    GLint textureUniform_ui = glGetUniformLocation(program.getProgramId(), "textureSampler");

    glEnableVertexAttribArray(posAttrib_ui);
    glVertexAttribPointer(posAttrib_ui, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(texCoordAttrib_ui);
    glVertexAttribPointer(texCoordAttrib_ui, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glUniform1i(textureUniform_ui, 0); // Assuming texture unit 0

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureid_ui); // Bind the loaded texture

    glDrawElements(GL_TRIANGLES,12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib_ui);
    glDisableVertexAttribArray(texCoordAttrib_ui);
    glUseProgram(0);
}