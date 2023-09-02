#include "verticalspeedindis.hpp"
#include <GLES2/gl2.h>
VSpeed::VSpeed(){

    program.attachShader("../shaders/vs-vertical.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-vertical.glsl", GL_FRAGMENT_SHADER);
    program.link();
    creatIndicator();

}

void VSpeed::creatIndicator(){
    
     GLfloat vertices_ind[] = {
        // Position (X, Y, Z)    

        0.925f,  0.40002f, 0.0f,     
        0.8f, 0.400002f, 0.0f,     
        0.925f, 0.40f, 0.0f,    
        0.8f, 0.40f, 0.0f,     

    };

    glGenBuffers(1, &vertexBuffer_ind);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_ind);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_ind), vertices_ind, GL_STATIC_DRAW);

    GLuint indices_ind[] = {
        0, 1, 2, // İlk üçgen
        1, 2,3, // İkinci üçgen
    };



    glGenBuffers(1, &indexBuffer_ind);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_ind);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_ind), indices_ind, GL_STATIC_DRAW);
}

void VSpeed::Draw_indicator(float yoffset){

    program.use();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_ind);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_ind);
    GLint posAttrib = glGetAttribLocation(program.getProgramId(),"position");
    GLint colorUniform = glGetUniformLocation(program.getProgramId(), "color");
    glUniform1f(glGetUniformLocation(program.getProgramId(), "modelYOffset"), yoffset);
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glUniform3f(colorUniform, 1.0f, 0.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);

    glUseProgram(0);
}
