#include "landscape.hpp"
#include <GLES2/gl2.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "VertexTypes.hpp"

Landscape::Landscape()
{

    program.attachShader("../shaders/vs-landscape.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-landscape.glsl", GL_FRAGMENT_SHADER);
    program.link();

    createLandscape();
    createLines();
}

void Landscape::Draw(float circleYPositions, float circleRotations)
{
    program.use();

    drawLandscape(circleYPositions, circleRotations);
    drawLines(circleYPositions, circleRotations);

    glUseProgram(0);
}

void Landscape::createLandscape()
{
    // Vertex verileri
    GLfloat vertices[] = {
        -2.0f,
        0.0f,
        0.0f,
        -2.0f,
        -2.0f,
        0.0f,
        2.0f,
        -2.0f,
        0.0f,
        2.0f,
        0.0f,
        0.0f,
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

void Landscape::createLines()
{
    const float gapValue = 0.1f;
    const float lineWidth = 0.14f;

    Vertex3List hl_Vertices;
    IndexList hl_Indices;

    Vertex3 vertex;

    // Yatay Çizgi Vertex verileri
    glm::vec3 horizontalLineVertices[] = {
        glm::vec3(-2.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 0.0f, 0.0f),

        glm::vec3(-lineWidth / 3, 0.0f + gapValue, 0.0f),
        glm::vec3(lineWidth / 3, 0.0f + gapValue, 0.0f),

        glm::vec3(-lineWidth / 3, 0.0f - gapValue, 0.0f),
        glm::vec3(lineWidth / 3, 0.0f - gapValue, 0.0f),

        glm::vec3(-lineWidth, 0.0f + gapValue * 2, 0.0f),
        glm::vec3(lineWidth, 0.0f + gapValue * 2, 0.0f),

        glm::vec3(-lineWidth, 0.0f - gapValue * 2, 0.0f),
        glm::vec3(lineWidth, 0.0f - gapValue * 2, 0.0f),

        glm::vec3(-lineWidth / 3, 0.0f + gapValue * 3, 0.0f),
        glm::vec3(lineWidth / 3, 0.0f + gapValue * 3, 0.0f),

        glm::vec3(-lineWidth / 3, 0.0f - gapValue * 3, 0.0f),
        glm::vec3(lineWidth / 3, 0.0f - gapValue * 3, 0.0f),

        glm::vec3(-lineWidth, 0.0f + gapValue * 4, 0.0f),
        glm::vec3(lineWidth, 0.0f + gapValue * 4, 0.0f),

        glm::vec3(-lineWidth, 0.0f - gapValue * 4, 0.0f),
        glm::vec3(lineWidth, 0.0f - gapValue * 4, 0.0f)

    };

    for (int i = 0; i < sizeof(horizontalLineVertices) / sizeof(horizontalLineVertices[0]); i++)
    {
        vertex.pos = horizontalLineVertices[i];
        hl_Vertices.push_back(vertex);
        hl_Indices.push_back(i);
    };

    lines_IndexCount = hl_Indices.size();

    glGenBuffers(1, &lines_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, lines_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3) * hl_Vertices.size(), &hl_Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &lines_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lines_IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * hl_Indices.size(), &hl_Indices[0], GL_STATIC_DRAW);
}

void Landscape::drawLandscape(float circleYPositions, float circleRotations)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.4f, 0.0f));
    model = glm::rotate(model, glm::radians(circleRotations), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(0.0f, circleYPositions, 0.0f));

    GLuint modelLoc = glGetUniformLocation(program.getProgramId(), "model");
    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint colorUniform = glGetUniformLocation(program.getProgramId(), "color");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(colorUniform, 0.424f, 0.341f, 0.208f);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
}

void Landscape::drawLines(float circleYPositions, float circleRotations)
{
    // Yatay çizgi çizimi

    glBindBuffer(GL_ARRAY_BUFFER, lines_VertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lines_IndexBuffer);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.4f, 0.0f));
    model = glm::rotate(model, glm::radians(circleRotations), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(0.0f, circleYPositions, 0.0f));
   

    GLuint modelLoc = glGetUniformLocation(program.getProgramId(), "model");
    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint colorUniform = glGetUniformLocation(program.getProgramId(), "color");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(colorUniform, 1.0f, 1.0f, 1.0f);
    
   
    if(circleYPositions>=0.085 && circleYPositions<0.185 )
    {
        glDrawArrays(GL_LINES,0,2); //orta çizgi
    glDrawArrays(GL_LINES,2,2); //4 4 5 arası orta çzigi
    glDrawArrays(GL_LINES,4,2); //5
   glDrawArrays(GL_LINES,6,2); //3
    glDrawArrays(GL_LINES,8,2); //*6
    glDrawArrays(GL_LINES,10,2);//2
    glDrawArrays(GL_LINES,12,2);//7

    glDrawArrays(GL_LINES,16,2); //8
        
    }
     if(circleYPositions>=0.185 && circleYPositions<0.285 )
    {
        glDrawArrays(GL_LINES,0,2); //orta çizgi
    glDrawArrays(GL_LINES,2,2); //4 4 5 arası orta çzigi
    glDrawArrays(GL_LINES,4,2); //5
   glDrawArrays(GL_LINES,6,2); //3
    glDrawArrays(GL_LINES,8,2); //*6
    glDrawArrays(GL_LINES,12,2);//7
    glDrawArrays(GL_LINES,16,2); //8
        
    }
     if(circleYPositions>=0.285 && circleYPositions<0.385 )
    {
        glDrawArrays(GL_LINES,0,2); //orta çizgi
    glDrawArrays(GL_LINES,2,2); //4 4 5 arası orta çzigi
    glDrawArrays(GL_LINES,4,2); //5
    glDrawArrays(GL_LINES,8,2); //*6
    glDrawArrays(GL_LINES,12,2);//7
    glDrawArrays(GL_LINES,16,2); //8
        
    }
     if(circleYPositions>=0.385  )
    {
        glDrawArrays(GL_LINES,0,2); //orta çizgi
    glDrawArrays(GL_LINES,4,2); //5
    glDrawArrays(GL_LINES,8,2); //*6
    glDrawArrays(GL_LINES,12,2);//7
    glDrawArrays(GL_LINES,16,2); //8
        
    }
    if(circleYPositions>-0.0145 && circleYPositions<0.085)
    {
        glDrawArrays(GL_LINES,0,2); //orta çizgi
    glDrawArrays(GL_LINES,2,2); //4 4 5 arası orta çzigi
    glDrawArrays(GL_LINES,4,2); //5
   glDrawArrays(GL_LINES,6,2); //3
    glDrawArrays(GL_LINES,8,2); //*6
    glDrawArrays(GL_LINES,10,2);//2
    glDrawArrays(GL_LINES,12,2);//7
    glDrawArrays(GL_LINES,14,2);//1
    glDrawArrays(GL_LINES,16,2); //8*/

    }

    if(circleYPositions<=-0.0145 && circleYPositions>-0.235 )
    {
       glDrawArrays(GL_LINES,0,2); //orta çizgi
    glDrawArrays(GL_LINES,2,2); //4 4 5 arası orta çzigi
    glDrawArrays(GL_LINES,4,2); //5
   glDrawArrays(GL_LINES,6,2); //3
    glDrawArrays(GL_LINES,8,2); //*6
    glDrawArrays(GL_LINES,10,2);//2
    glDrawArrays(GL_LINES,12,2);//7
    glDrawArrays(GL_LINES,14,2);//1
        
    }
     if(circleYPositions<=-0.235 && circleYPositions>-0.335 )
    {
          glDrawArrays(GL_LINES,0,2); //orta çizgi
    glDrawArrays(GL_LINES,2,2); //4 4 5 arası orta çzigi
    glDrawArrays(GL_LINES,4,2); //5
   glDrawArrays(GL_LINES,6,2); //3
    glDrawArrays(GL_LINES,8,2); //*6
    glDrawArrays(GL_LINES,10,2);//2

    glDrawArrays(GL_LINES,14,2);//1
    
        
    }
     if(circleYPositions<=-0.285 && circleYPositions>-0.385 )
    {
      glDrawArrays(GL_LINES,0,2); //orta çizgi
    glDrawArrays(GL_LINES,2,2); //4 4 5 arası orta çzigi
    glDrawArrays(GL_LINES,4,2); //5
   glDrawArrays(GL_LINES,6,2); //3
    glDrawArrays(GL_LINES,10,2);//2

    glDrawArrays(GL_LINES,14,2);//1
        
    }
     if(circleYPositions<=-0.385  )
    {glDrawArrays(GL_LINES,0,2); //orta çizgi
    glDrawArrays(GL_LINES,2,2); //4 4 5 arası orta çzigi
   glDrawArrays(GL_LINES,6,2); //3
    glDrawArrays(GL_LINES,10,2);//2
    glDrawArrays(GL_LINES,14,2);//1
        
    }
 
 
    //glDrawElements(GL_LINES, Indices.size(), GL_UNSIGNED_INT, 0);
   /*glDrawArrays(GL_LINES,0,2); //orta çizgi
    glDrawArrays(GL_LINES,2,2); //4 4 5 arası orta çzigi
    glDrawArrays(GL_LINES,4,2); //5
   glDrawArrays(GL_LINES,6,2); //3
    glDrawArrays(GL_LINES,8,2); //6
    glDrawArrays(GL_LINES,10,2);//2
    glDrawArrays(GL_LINES,12,2);//7
    glDrawArrays(GL_LINES,14,2);//1
    glDrawArrays(GL_LINES,16,2); //8*/


  
    glDisableVertexAttribArray(posAttrib);
}
