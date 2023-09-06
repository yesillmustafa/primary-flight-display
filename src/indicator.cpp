#include "indicator.hpp"
#include <GLES2/gl2.h>
#include <iostream>
#include "VertexTypes.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

Indicator::Indicator() {

    program.attachShader("../shaders/vs-indicator.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-indicator.glsl", GL_FRAGMENT_SHADER);
    program.link();

    createIndicator1();
    createIndicator2();
    

}

void Indicator::Draw() {
    
    program.use();

    drawIndicator1();
    drawIndicator2();

    glUseProgram(0);
}

void Indicator::createIndicator1()
{
    Vertex3List vertices;
    const float lineWidth = 0.06f;
    Vertex3 vertex;

    // Hız Göstergesi
    vertex.pos = glm::vec3 (-0.48f, 0.21f, 0.0f);         // 0
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 (-0.48f-lineWidth, 0.21f, 0.0f);   //1
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 (-0.5f-lineWidth, 0.20f, 0.0f);    //2
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 ( -0.48f-lineWidth, 0.19f, 0.0f);         //3
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 ( -0.48f, 0.19f, 0.0f);         //4
    vertices.push_back(vertex);

    // Yükseklik Göstergesi
    vertex.pos = glm::vec3 (0.48f, 0.21f, 0.0f);         // 5
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 (0.48f+lineWidth, 0.21f, 0.0f);   //6
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 (0.5f+lineWidth, 0.20f, 0.0f);    //7
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 ( 0.48f+lineWidth, 0.19f, 0.0f);         //8
    vertices.push_back(vertex);
    vertex.pos = glm::vec3 ( 0.48f, 0.19f, 0.0f);         //9
    vertices.push_back(vertex);

    
    GLuint indices[] = {0,4,1,3,4,1,1,2,3,5,9,6,8,9,6,6,7,8};


    glGenBuffers(1, &vertexBuffer1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3)*vertices.size(),&vertices[0], GL_STATIC_DRAW);

    
    glGenBuffers(1, &indexBuffer1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);
    
    indexCount1 = sizeof(indices);
}

void Indicator::createIndicator2()
{
    Vertex3List vertices;
    IndexList indices;
    float radius= 0.42f;
    float innerRadius = 0.385f;
    float temp=2.5f;
    int numTriangles = 8;
    int numVertices = numTriangles * 3;
    float angle = 360.0f / numTriangles;

    for (int i = 0; i <= numTriangles; i++)
    {
        float newAngle = i * angle;
        float newAngle1 = (i* angle) -temp ;
        float newAngle2 = (i* angle) +temp ;
        float x1 = radius * cos(glm::radians(newAngle1));
        float y1 = radius * sin(glm::radians(newAngle1));
        float z1 = 0.0f;
        float x2 = radius * cos(glm::radians(newAngle2));
        float y2 = radius * sin(glm::radians(newAngle2));
        float z2 = 0.0f;
        float x3 = innerRadius * cos(glm::radians(newAngle));
        float y3 = innerRadius * sin(glm::radians(newAngle));
        float z3 = 0.0f;

        Vertex3 vertex1;
        Vertex3 vertex2;
        Vertex3 vertex3;

        vertex1.pos = glm::vec3(x1, y1, z1);
        vertex2.pos = glm::vec3(x2, y2, z2);
        vertex3.pos = glm::vec3(x3, y3, z3);
        vertices.push_back(vertex1);
        vertices.push_back(vertex2);
        vertices.push_back(vertex3);

    }
    for (int i = 0; i <= numTriangles ; i++) {
        indices.push_back(i*3);
        indices.push_back(i*3+1);
        indices.push_back(i*3+2);
    }

    glGenBuffers(1, &vertexBuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3)*vertices.size(),&vertices[0], GL_STATIC_DRAW);

    
    glGenBuffers(1, &indexBuffer2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(),&indices[0], GL_STATIC_DRAW);
    
    indexCount2 = indices.size();
}

void Indicator::drawIndicator1()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer1);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));

    GLuint modelLoc = glGetUniformLocation(program.getProgramId(),"model");
    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint colorUniform = glGetUniformLocation(program.getProgramId(), "color");

    glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(colorUniform, 1.0f, 1.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, indexCount1, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
}

void Indicator::drawIndicator2()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer2);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5625f, 0.0f));

    GLuint modelLoc = glGetUniformLocation(program.getProgramId(),"model");
    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint colorUniform = glGetUniformLocation(program.getProgramId(), "color");

    glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(colorUniform, 1.0f, 1.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, indexCount2, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
}