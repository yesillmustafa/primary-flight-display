#include "aircraft.hpp"
#include <GLES2/gl2.h>
#include <iostream>
#include "VertexTypes.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

Aircraft::Aircraft() {

    program.attachShader("../shaders/vs-indicator.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-indicator.glsl", GL_FRAGMENT_SHADER);
    program.link();
    
    createAircraftAI();
    createAircraftHI();

}

void Aircraft::Draw() {
    program.use();

    drawAircraftAI();
    drawAircraftHI();

    glUseProgram(0);
}

void Aircraft::createAircraftAI()
{
    Vertex3List vertices;
    Vertex3 vertex;
    const float lineWidth = 0.15f;

    // Orta Gösterge
    vertex.pos = glm::vec3 (0.0f, 0.20f, 0.0f);         // 0
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 (-lineWidth, 0.14f, 0.0f);   //1
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 (lineWidth, 0.14f, 0.0f);    //2
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 (0.0f, 0.16f, 0.0f);         //3
    vertices.push_back(vertex);

    // Sol Gösterge
    vertex.pos = glm::vec3 (-0.45f, 0.21f, 0.0f);         // 4
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 (-0.45f+lineWidth, 0.21f, 0.0f);   //5
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 (-0.43f+lineWidth, 0.20f, 0.0f);    //6
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 ( -0.45f+lineWidth, 0.19f, 0.0f);         //7
    vertices.push_back(vertex);
     vertex.pos = glm::vec3 ( -0.45f, 0.19f, 0.0f);         //8
    vertices.push_back(vertex);

    // Sağ Gösterge
    vertex.pos = glm::vec3 (0.45f, 0.21f, 0.0f);         // 9
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 ( 0.45f-lineWidth, 0.21f, 0.0f);   //10
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 ( 0.43f-lineWidth, 0.20f, 0.0f);    //11
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 (  0.45f-lineWidth, 0.19f, 0.0f);         //12
    vertices.push_back(vertex);
     vertex.pos = glm::vec3 ( 0.45f, 0.19f, 0.0f );         //13
    vertices.push_back(vertex);

    glGenBuffers(1, &AI_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, AI_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3)*vertices.size(),&vertices[0], GL_STATIC_DRAW);

    // İndeks verileri
    GLuint indices[] = {0,1,3,0,2,3,4,8,5,7,8,5,5,6,7,9,10,13,10,12,13,10,11,12};

    glGenBuffers(1, &AI_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AI_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Aircraft::createAircraftHI()
{
    Vertex3List vertices;
    Vertex3 vertex;

    vertex.pos = glm::vec3(0.0f,   -0.02f,   0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(0.0f,   -0.05,   0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(0.0f,   0.05,   0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(0.01f,  0.04,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(0.01f,  0.005f,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(0.05,  -0.015f,    0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3( 0.05,  -0.02f,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(0.01f, -0.02f,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(0.01f, -0.04,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(0.015f, -0.04,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(0.02f,  -0.05,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(-0.02f,  -0.05,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(-0.015f, -0.04,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(-0.01f, -0.04,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(-0.01f, -0.02f,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(-0.05,  -0.02f,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(-0.05,  -0.015f,    0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(-0.01f,  0.005f,  0.0f);
    vertices.push_back(vertex);
    vertex.pos = glm::vec3(-0.01f,  0.04,  0.0f);
    vertices.push_back(vertex);


    glGenBuffers(1, &HI_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, HI_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3)*vertices.size(),&vertices[0], GL_STATIC_DRAW);

    // İndeks verileri
    GLuint indices[] = {0,2,3,
                        0,3,4,
                        0,4,5,
                        0,5,6,
                        0,7,8,
                        0,1,8,
                        1,8,9,
                        1,9,10,
                        1,11,12,
                        1,12,13,
                        0,1,13,
                        0,13,14,
                        0,15,16,
                        0,16,17,
                        0,17,18,
                        0,2,18
                        };

    glGenBuffers(1, &HI_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, HI_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 
}

void Aircraft::drawAircraftAI()
{
    glBindBuffer(GL_ARRAY_BUFFER, AI_vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AI_indexBuffer);

    glm::mat4 aiModel = glm::mat4(1.0f);
    aiModel = glm::translate(aiModel, glm::vec3(0.0f, 0.2f, 0.0f));

    GLuint aiModelLoc = glGetUniformLocation(program.getProgramId(),"model");
    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint colorUniform = glGetUniformLocation(program.getProgramId(), "color");

    glUniformMatrix4fv(aiModelLoc,1,GL_FALSE,glm::value_ptr(aiModel));
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(colorUniform, 1.0f, 1.0f, 0.0f);

    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
}

void Aircraft::drawAircraftHI()
{
    glBindBuffer(GL_ARRAY_BUFFER, HI_vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, HI_indexBuffer);

    glm::mat4 hiModel = glm::mat4(1.0f);
    hiModel = glm::translate(hiModel, glm::vec3(0.0f, -0.5625f, 0.0f));

    GLuint hiModelLoc = glGetUniformLocation(program.getProgramId(),"model");
    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint colorUniform = glGetUniformLocation(program.getProgramId(), "color");

    glUniformMatrix4fv(hiModelLoc,1,GL_FALSE,glm::value_ptr(hiModel));
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(colorUniform, 1.0f, 1.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, 57, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
}