#include "AttitudeIndicator.hpp"
#include <GLES2/gl2.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>

#include "VertexTypes.hpp"

AttitudeIndicator::AttitudeIndicator() {

    program.attachShader("../shaders/vs-landscape.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-landscape.glsl", GL_FRAGMENT_SHADER);
    program.link();

    createArcScaleLines();
    //createArc();
    createArcTriangle();
    createBankAngle();
    createSlipSkidIndicator();

}

void AttitudeIndicator::Draw(float circleYPositions, float circleRotations, float slipskid) {
    program.use();

    drawArcScaleLines(circleYPositions,circleRotations);
    //drawArc(circleYPositions, circleRotations);
    drawArcTriangle(circleYPositions,circleRotations);
    drawBankAngle(circleYPositions,circleRotations);
    drawSlipSkidIndicator(circleYPositions,circleRotations,slipskid);
    
    glUseProgram(0);
}


void AttitudeIndicator::createArcScaleLines()
{
    // Yay üzerindeki Ölçek Çizgileri

    Vertex3List sl_Vertices;
    IndexList sl_Indices;

    Vertex3 scaleVertex;

    float radius = 0.5f;
    float innerRadius1 = 0.53f;
    float innerRadius2 = 0.57f;
glm::vec3 arcScaleVertices[] = {
    glm::vec3(radius * cos(glm::radians(30.0f)), radius * sin(glm::radians(30.0f)) , 0.0f),
    glm::vec3(innerRadius2 * cos(glm::radians(30.0f)), innerRadius2 * sin(glm::radians(30.0f)) , 0.0f),

    glm::vec3(radius * cos(glm::radians(45.0f)), radius * sin(glm::radians(45.0f)) , 0.0f),
    glm::vec3(innerRadius1 * cos(glm::radians(45.0f)), innerRadius1 * sin(glm::radians(45.0f)) , 0.0f),

    glm::vec3(radius * cos(glm::radians(60.0f)), radius * sin(glm::radians(60.0f)) , 0.0f),
    glm::vec3(innerRadius2 * cos(glm::radians(60.0f)), innerRadius2 * sin(glm::radians(60.0f)) , 0.0f),

    glm::vec3(radius * cos(glm::radians(70.0f)), radius * sin(glm::radians(70.0f)) , 0.0f),
    glm::vec3(innerRadius1 * cos(glm::radians(70.0f)), innerRadius1 * sin(glm::radians(70.0f)) , 0.0f),

    glm::vec3(radius * cos(glm::radians(80.0f)), radius * sin(glm::radians(80.0f)) , 0.0f),
    glm::vec3(innerRadius1 * cos(glm::radians(80.0f)), innerRadius1 * sin(glm::radians(80.0f)) , 0.0f),

    glm::vec3(radius * cos(glm::radians(100.0f)), radius * sin(glm::radians(100.0f)) , 0.0f),
    glm::vec3(innerRadius1 * cos(glm::radians(100.0f)), innerRadius1 * sin(glm::radians(100.0f)) , 0.0f),

    glm::vec3(radius * cos(glm::radians(110.0f)), radius * sin(glm::radians(110.0f)) , 0.0f),
    glm::vec3(innerRadius1 * cos(glm::radians(110.0f)), innerRadius1 * sin(glm::radians(110.0f)) , 0.0f),

    glm::vec3(radius * cos(glm::radians(120.0f)), radius * sin(glm::radians(120.0f)) , 0.0f),
    glm::vec3(innerRadius2 * cos(glm::radians(120.0f)), innerRadius2 * sin(glm::radians(120.0f)) , 0.0f),

    glm::vec3(radius * cos(glm::radians(135.0f)), radius * sin(glm::radians(135.0f)) , 0.0f),
    glm::vec3(innerRadius1 * cos(glm::radians(135.0f)), innerRadius1 * sin(glm::radians(135.0f)) , 0.0f),

    glm::vec3(radius * cos(glm::radians(150.0f)), radius * sin(glm::radians(150.0f)) , 0.0f),
    glm::vec3(innerRadius2 * cos(glm::radians(150.0f)), innerRadius2 * sin(glm::radians(150.0f)) , 0.0f)
};


    for(int i=0;i<sizeof(arcScaleVertices) / sizeof(arcScaleVertices[0]);i++)
    {
        scaleVertex.pos = arcScaleVertices[i];
        sl_Vertices.push_back(scaleVertex);
        sl_Indices.push_back(i);
    };

    arcScaleLines_IndexCount = sl_Indices.size();

    glGenBuffers(1, &arcScaleLines_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, arcScaleLines_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex3)*sl_Vertices.size(),&sl_Vertices[0],GL_STATIC_DRAW);

    glGenBuffers(1, &arcScaleLines_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arcScaleLines_IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*sl_Indices.size(),&sl_Indices[0],GL_STATIC_DRAW);

}

void AttitudeIndicator::createArc()
{
    // Çember Yayı vertex ve index verileri

    float arcRadius = 0.5f; // Çemberin yarıçapı
    int numSegments = 120; // İstenilen segment sayısı (120 derece)
    float arcStep = glm::radians(120.0f) / numSegments; // Adım hesaplama

    Vertex3List arc_Vertices;
    IndexList arc_Indices;

    Vertex3 arcVertex;

    for (int i = 0; i <= numSegments; i++) {
        float angle = glm::radians(30.0f) + arcStep * i;
        arcVertex.pos = glm::vec3(arcRadius * cos(angle), arcRadius * sin(angle)+0.18f, 0.0f);
        arc_Vertices.push_back(arcVertex);
        arc_Indices.push_back(i);
    }   

    arc_IndexCount = arc_Indices.size();

    glGenBuffers(1, &arc_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, arc_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3) * arc_Vertices.size(), &arc_Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &arc_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arc_IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * arc_Indices.size(), &arc_Indices[0], GL_STATIC_DRAW);
}

void AttitudeIndicator::createArcTriangle()
{
    Vertex3List arcTri_Vertices;
    IndexList arcTri_Indices;

    Vertex3 arcTriVertex;

    float radius = 0.5f;
    float innerRadius = 0.55f;
    
    glm::vec3 triangleVertices[] = {
        glm::vec3(radius*cos(glm::radians(90.0f)),radius*sin(glm::radians(90.0f)),0.0f),
        glm::vec3(innerRadius*cos(glm::radians(92.5f)),innerRadius*sin(glm::radians(92.5f)),0.0f),
        glm::vec3(innerRadius*cos(glm::radians(87.5f)),innerRadius*sin(glm::radians(87.5f)),0.0f)
    };

    for(int i=0; i<3; i++)
    {
        arcTriVertex.pos = triangleVertices[i];
        arcTri_Vertices.push_back(arcTriVertex);
        arcTri_Indices.push_back(i);
    }

    arcTriangle_IndexCount = arcTri_Indices.size();

    glGenBuffers(1, &arcTriangle_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, arcTriangle_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3) * arcTri_Vertices.size(), &arcTri_Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &arcTriangle_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arcTriangle_IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * arcTri_Indices.size(), &arcTri_Indices[0], GL_STATIC_DRAW);
}

void AttitudeIndicator::createBankAngle()
{
    Vertex3List bankAngle_Vertices;
    IndexList bankAngle_Indices;

    Vertex3 bankAngleVertex;

    float radius = 0.475f;
    float innerRadius = 0.43f;
    
    glm::vec3 triangleVertices[] = {
        glm::vec3(radius*cos(glm::radians(90.0f)),radius*sin(glm::radians(90.0f)),0.0f),
        glm::vec3(innerRadius*cos(glm::radians(93.0f)),innerRadius*sin(glm::radians(93.0f)),0.0f),
        glm::vec3(innerRadius*cos(glm::radians(87.0f)),innerRadius*sin(glm::radians(87.0f)),0.0f)
    };

    for(int i=0; i<3; i++)
    {
        bankAngleVertex.pos = triangleVertices[i];
        bankAngle_Vertices.push_back(bankAngleVertex);
        bankAngle_Indices.push_back(i);
    }

    bankAngle_IndexCount = bankAngle_Indices.size();

    glGenBuffers(1, &bankAngle_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bankAngle_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3) * bankAngle_Vertices.size(), &bankAngle_Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &bankAngle_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bankAngle_IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * bankAngle_Indices.size(), &bankAngle_Indices[0], GL_STATIC_DRAW);
}

void AttitudeIndicator::createSlipSkidIndicator()
{
    Vertex3List slipSkid_Vertices;
    IndexList slipSkid_Indices;

    Vertex3 slipSkidVertex;

    float radius = 0.42f;
    float innerRadius = 0.4f;
    glm::vec3 triangleVertices[] = {
        glm::vec3(radius*cos(glm::radians(93.0f)),radius*sin(glm::radians(93.0f)),0.0f),
        glm::vec3(radius*cos(glm::radians(87.0f)),radius*sin(glm::radians(87.0f)),0.0f),
        glm::vec3(innerRadius*cos(glm::radians(94.0f)),innerRadius*sin(glm::radians(94.0f)),0.0f),
        glm::vec3(innerRadius*cos(glm::radians(86.0f)),innerRadius*sin(glm::radians(86.0f)),0.0f)
    };

    for(int i=0; i<4; i++)
    {
        slipSkidVertex.pos = triangleVertices[i];
        slipSkid_Vertices.push_back(slipSkidVertex);
        slipSkid_Indices.push_back(i);
    }

    slipSkid_IndexCount = slipSkid_Indices.size();

    glGenBuffers(1, &slipSkid_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, slipSkid_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3) * slipSkid_Vertices.size(), &slipSkid_Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &slipSkid_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, slipSkid_IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * slipSkid_Indices.size(), &slipSkid_Indices[0], GL_STATIC_DRAW);
}


void AttitudeIndicator::drawArcScaleLines(float circleYPositions, float circleRotations)
{
    // Yay üzerindeki ölçek çizgilerin çizimi

    glBindBuffer(GL_ARRAY_BUFFER, arcScaleLines_VertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arcScaleLines_IndexBuffer);

    glm::mat4 scaleModel = glm::mat4(1.0f);
    scaleModel = glm::translate(scaleModel, glm::vec3(0.0f, 0.4f, 0.0f));
    //scaleModel = glm::rotate(scaleModel,glm::radians(circleRotations), glm::vec3(0.0f,0.0f,1.0f));

    GLuint scaleModelLoc = glGetUniformLocation(program.getProgramId(),"model");
    GLint scalePosAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint scaleColorUniform = glGetUniformLocation(program.getProgramId(), "color");

    glUniformMatrix4fv(scaleModelLoc,1,GL_FALSE,glm::value_ptr(scaleModel));
    glEnableVertexAttribArray(scalePosAttrib);
    glVertexAttribPointer(scalePosAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(scaleColorUniform, 1.0f, 1.0f, 1.0f);

    glDrawElements(GL_LINES, arcScaleLines_IndexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(scalePosAttrib);
}

void AttitudeIndicator::drawArc(float circleYPositions, float circleRotations)
{
    //  Çember yayı çizimi
    
    glBindBuffer(GL_ARRAY_BUFFER, arc_VertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arc_IndexBuffer);

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

    glDrawElements(GL_LINE_STRIP, arc_IndexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(arcPosAttrib);
}

void AttitudeIndicator::drawArcTriangle(float circleYPositions, float circleRotations)
{
    //  Yaydaki Üçgenin çizimi
    
    glBindBuffer(GL_ARRAY_BUFFER, arcTriangle_VertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arcTriangle_IndexBuffer);

    glm::mat4 arcTriModel = glm::mat4(1.0f);
    arcTriModel = glm::translate(arcTriModel, glm::vec3(0.0f, 0.4f, 0.0f)); //çemberin konumu
    //arcTriModel = glm::rotate(arcTriModel,glm::radians(circleRotations), glm::vec3(0.0f,0.0f,1.0f));

    GLuint arcTriModelLoc = glGetUniformLocation(program.getProgramId(), "model");
    GLint arcTriPosAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint arcTriColorUniform = glGetUniformLocation(program.getProgramId(), "color");

    glUniformMatrix4fv(arcTriModelLoc, 1, GL_FALSE, glm::value_ptr(arcTriModel));
    glEnableVertexAttribArray(arcTriPosAttrib);
    glVertexAttribPointer(arcTriPosAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(arcTriColorUniform, 1.0f, 1.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, arcTriangle_IndexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(arcTriPosAttrib);
}

void AttitudeIndicator::drawBankAngle(float circleYPositions, float circleRotations)
{
    //  Yaydaki Üçgenin çizimi
    
    glBindBuffer(GL_ARRAY_BUFFER, bankAngle_VertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bankAngle_IndexBuffer);

    glm::mat4 bankAngleModel = glm::mat4(1.0f);
    bankAngleModel = glm::translate(bankAngleModel, glm::vec3(0.0f, 0.4f, 0.0f)); //çemberin konumu
    bankAngleModel = glm::rotate(bankAngleModel,glm::radians(circleRotations), glm::vec3(0.0f,0.0f,1.0f));

    GLuint bankAngleModelLoc = glGetUniformLocation(program.getProgramId(), "model");
    GLint bankAnglePosAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint bankAngleColorUniform = glGetUniformLocation(program.getProgramId(), "color");

    glUniformMatrix4fv(bankAngleModelLoc, 1, GL_FALSE, glm::value_ptr(bankAngleModel));
    glEnableVertexAttribArray(bankAnglePosAttrib);
    glVertexAttribPointer(bankAnglePosAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(bankAngleColorUniform, 1.0f, 1.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, bankAngle_IndexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(bankAnglePosAttrib);
}

void AttitudeIndicator::drawSlipSkidIndicator(float circleYPositions, float circleRotations, float slipskid)
{
    //  Yaydaki Üçgenin çizimi
    
    glBindBuffer(GL_ARRAY_BUFFER, slipSkid_VertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, slipSkid_IndexBuffer);

    glm::mat4 slipSkidModel = glm::mat4(1.0f);
    slipSkidModel = glm::translate(slipSkidModel, glm::vec3(0.0f, 0.4f, 0.0f)); //çemberin konumu
    slipSkidModel = glm::rotate(slipSkidModel,glm::radians(circleRotations), glm::vec3(0.0f,0.0f,1.0f));
    slipSkidModel = glm::translate(slipSkidModel,glm::vec3(slipskid,0.0f, 0.0f));
    GLuint slipSkidModelLoc = glGetUniformLocation(program.getProgramId(), "model");
    GLint slipSkidPosAttrib = glGetAttribLocation(program.getProgramId(), "position");
    GLint slipSkidColorUniform = glGetUniformLocation(program.getProgramId(), "color");

    glUniformMatrix4fv(slipSkidModelLoc, 1, GL_FALSE, glm::value_ptr(slipSkidModel));
    glEnableVertexAttribArray(slipSkidPosAttrib);
    glVertexAttribPointer(slipSkidPosAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glUniform3f(slipSkidColorUniform, 1.0f, 1.0f, 1.0f);

    glDrawElements(GL_TRIANGLE_STRIP, slipSkid_IndexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(slipSkidPosAttrib);
}