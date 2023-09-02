#include "HeadingIndicator.hpp"
#include <GLES2/gl2.h>
#include <iostream>
#include "TextureManager.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "VertexTypes.hpp"


HeadingIndicator::HeadingIndicator() {
    program.attachShader("../shaders/vs-hitexture.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fs-hitexture.glsl", GL_FRAGMENT_SHADER);
    program.link();

     // Çember Yayı vertex ve index verileri

    Vertex3TexList vertices;
    IndexList indices;

    float radius = 0.375f;
    int numSegments = 72;

    float angle = 360.0f / numSegments;
    int vertexCount = numSegments + 1; // Include the center vertex

    vertices.clear();
    indices.clear();

    Vertex3Tex centerVertex;
    centerVertex.pos = glm::vec3(0.0f, 0.0f, 0.0f);
    centerVertex.tex = glm::vec2(0.5f, 0.5f); // Texture center coordinates
    vertices.push_back(centerVertex);

    for (int i = 0; i < vertexCount; i++) {
        float newAngle = i * angle;
        float x = radius * cos(glm::radians(newAngle));
        float y = radius * sin(glm::radians(newAngle));
        float z = 0.0f;

        Vertex3Tex vertex;
        vertex.pos = glm::vec3(x, y, z);
        vertex.tex = glm::vec2((cos(glm::radians(newAngle)) + 1.0f) * 0.5f, (sin(glm::radians(newAngle)) + 1.0f) * 0.5f);
        vertices.push_back(vertex);
    }
    for (int i = 0; i < numSegments; i++) {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }

    indexCount = indices.size();

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3Tex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    hiTex = TextureManager::getInstance()->loadTexture("../images/hi.png");

}

void HeadingIndicator::Draw(float circleYPositions, float circleRotations) {
    program.use();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5625f, 0.0f)); //çemberin konumu
    model = glm::rotate(model,glm::radians(circleRotations), glm::vec3(0.0f,0.0f,1.0f));

    GLint posAttrib = glGetAttribLocation(program.getProgramId(), "a_position");
    GLint texCoordAttrib = glGetAttribLocation(program.getProgramId(), "texCoord");
    GLint textureUniform = glGetUniformLocation(program.getProgramId(), "textureSampler");
    GLuint modelLoc = glGetUniformLocation(program.getProgramId(), "model");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(texCoordAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glUniform1i(textureUniform, 1); // Assuming texture unit 0

    //activate texture
    TextureManager::getInstance()->activateTexture(GL_TEXTURE1,hiTex);

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(posAttrib);
    glDisableVertexAttribArray(texCoordAttrib);

    glUseProgram(0);
}

