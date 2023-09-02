#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class Aircraft {
public:
    Aircraft();
    void Draw();
private:
    void createAircraftAI();
    void createAircraftHI();

    void drawAircraftAI();
    void drawAircraftHI();

    float height=0.0;
    ShaderProgram program;
    GLuint AI_vertexBuffer;
    GLuint AI_indexBuffer;
    GLuint HI_vertexBuffer;
    GLuint HI_indexBuffer;
};

#endif // AIRCRAFT_HPP
