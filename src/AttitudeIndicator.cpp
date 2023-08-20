#include "AttitudeIndicator.hpp"
#include <GLES2/gl2.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>

AttitudeIndicator::AttitudeIndicator() {

    program.attachShader("../shaders/vs-landscape.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-landscape.glsl", GL_FRAGMENT_SHADER);
    program.link();

    const float gapValue = 0.08f;
    const float lineWidth = 0.14f;

    // Yatay Çizgi Vertex verileri
    GLfloat vertices[] = {
        -2.0f, 0.0f, 0.0f,
        2.0f, 0.0f, 0.0f,

        -lineWidth/3, 0.0f + gapValue, 0.0f,
        lineWidth/3, 0.0f + gapValue, 0.0f,

        -lineWidth/3, 0.0f - gapValue, 0.0f,
        lineWidth/3, 0.0f - gapValue, 0.0f,

        -lineWidth, 0.0f + gapValue*2, 0.0f,
        lineWidth, 0.0f + gapValue*2, 0.0f,

        -lineWidth, 0.0f - gapValue*2, 0.0f,
        lineWidth, 0.0f - gapValue*2, 0.0f,

        -lineWidth/3, 0.0f + gapValue*3, 0.0f,
        lineWidth/3, 0.0f + gapValue*3, 0.0f,

        -lineWidth/3, 0.0f - gapValue*3, 0.0f,
        lineWidth/3, 0.0f - gapValue*3, 0.0f,

        -lineWidth, 0.0f + gapValue*4, 0.0f,
        lineWidth, 0.0f + gapValue*4, 0.0f,

        -lineWidth, 0.0f - gapValue*4, 0.0f,
        lineWidth, 0.0f - gapValue*4, 0.0f


    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Yatay Çizgi İndeks verileri
    GLuint indices[] = {0, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Çember Yayı vertex ve index verileri

    float arcRadius = 0.6f; // Çemberin yarıçapı
    int numSegments = 360; // İstenilen segment sayısı
    float arcStep = glm::radians(360.0f / static_cast<float>(numSegments)); // Adım hesaplama
    float startAngleDegrees = 30.0f;
    float startAngleRadians = glm::radians(startAngleDegrees);

    GLfloat arcVertices[(numSegments + 1) * 3]; // +1 merkez noktası için
    GLuint arcIndices[numSegments * 2]; // Her iki nokta arası çizgi

    for (int i = 0; i <= numSegments; i++) {
        float angle = startAngleRadians + arcStep * i;
        float x = arcRadius * cos(angle);
        float y = arcRadius * sin(angle);

        arcVertices[i * 3] = x;
        arcVertices[i * 3 + 1] = y;
        arcVertices[i * 3 + 2] = 0.0f;

        if (i < numSegments) {
            arcIndices[i * 2] = i;
            arcIndices[i * 2 + 1] = i + 1;
        }
    }   

    glGenBuffers(1, &arcVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, arcVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arcVertices), arcVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &arcIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arcIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arcIndices), arcIndices, GL_STATIC_DRAW);


}

void AttitudeIndicator::Draw(float circleYPositions, float circleRotations) {
    program.use();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    // Yatay çizgi çizimi

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
    glUniform3f(colorUniform, 1.0f, 1.0f, 1.0f);

    glDrawElements(GL_LINES, 18, GL_UNSIGNED_INT, 0);



    //  Çember yayı çizimi
    
    glBindBuffer(GL_ARRAY_BUFFER, arcVertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arcIndexBuffer);
    glm::mat4 arcModel = glm::mat4(1.0f);
    arcModel = glm::translate(arcModel, glm::vec3(0.0f, 0.2f, 0.0f)); //çemberin konumu
    arcModel = glm::rotate(arcModel,glm::radians(circleRotations), glm::vec3(0.0f,0.0f,1.0f));
    GLuint arcModelLoc = glGetUniformLocation(program.getProgramId(), "model");
    GLint arcPosAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint arcColorUniform = glGetUniformLocation(program.getProgramId(), "color");
    glUniformMatrix4fv(arcModelLoc, 1, GL_FALSE, glm::value_ptr(arcModel));
    glEnableVertexAttribArray(arcPosAttrib);
    glVertexAttribPointer(arcPosAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(arcColorUniform, 1.0f, 1.0f, 1.0f);

    glDrawElements(GL_LINES, 120*2, GL_UNSIGNED_INT, 0);



    glDisableVertexAttribArray(posAttrib);
    glUseProgram(0);
}
