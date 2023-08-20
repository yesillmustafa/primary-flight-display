#include "aircraft.hpp"
#include <GLES2/gl2.h>
#include <iostream>

Aircraft::Aircraft() {

    program.attachShader("../shaders/vs-indicator.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-indicator.glsl", GL_FRAGMENT_SHADER);
    program.link();

    const float lineWidth = 0.16f;

    // Vertex verileri
    GLfloat vertices[] = {
        // Orta Gösterge
        0.0f, 0.20f, 0.0f,              // 0
        -lineWidth, 0.14f, 0.0f,            // 1    
        lineWidth, 0.14f, 0.0f,             // 2
        0.0f, 0.16f, 0.0f,              // 3

        // Sol Gösterge
        -0.5f, 0.21f, 0.0f,             // 4
        -0.5f+lineWidth, 0.21f, 0.0f,   // 5
        -0.49f+lineWidth, 0.20f, 0.0f,  // 6
        -0.5f+lineWidth, 0.19f, 0.0f,   // 7
        -0.5f, 0.19f, 0.0f,             // 8

        // Sağ Gösterge
        0.5f, 0.21f, 0.0f,             // 9
        0.5f-lineWidth, 0.21f, 0.0f,   // 10
        0.49f-lineWidth, 0.20f, 0.0f,  // 11
        0.5f-lineWidth, 0.19f, 0.0f,   // 12
        0.5f, 0.19f, 0.0f             // 13

    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // İndeks verileri
    GLuint indices[] = {0,1,3,0,2,3,4,8,5,7,8,5,5,6,7,9,10,13,10,12,13,10,11,12};

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Aircraft::Draw() {
    program.use();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint colorUniform = glGetUniformLocation(program.getProgramId(), "color");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(colorUniform, 1.0f, 1.0f, 0.0f);

    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
    glUseProgram(0);
}
