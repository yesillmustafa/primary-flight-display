#include "landscape.hpp"
#include <GLES2/gl2.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>

Landscape::Landscape(){

    program.attachShader("../shaders/vs-landscape.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-landscape.glsl", GL_FRAGMENT_SHADER);
    program.link();
    const float height=0.3f;
    // Vertex verileri
    GLfloat vertices[] = {
        -2.0f, 0.0f+height, 0.0f,
        -2.0f, -2.0f+height, 0.0f,
        2.0f, -2.0f+height, 0.0f,
        2.0f, 0.0f+height, 0.0f,
    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // İndeks verileri
    GLuint indices[] = {0, 1, 2, 0, 2, 3};

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}


void Landscape::Draw(float circleYPositions, float circleRotations) {
    program.use();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
    model = glm::rotate(model,glm::radians(circleRotations), glm::vec3(0.0f,0.0f,1.0f));
    model = glm::translate(model,glm::vec3(0.0f,circleYPositions, 0.0f));
    
    GLuint modelLoc = glGetUniformLocation(program.getProgramId(),"model");
    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint colorUniform = glGetUniformLocation(program.getProgramId(), "color");
    glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(colorUniform, 0.424f, 0.341f, 0.208f);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
    glUseProgram(0);
}

