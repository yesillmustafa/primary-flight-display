#ifndef MATHEMATICS_HPP
#define MATHEMATICS_HPP

#include <GLES2/gl2.h>
#include "shaderProgram.hpp"

class MATH
{
public:
    float calculataVSI(float pitchValue,float speedValue );
    float calculateAltitude(float passingTime);
    float calculateRadyan();
private : 
    float hspeedValue=0.0f;
    float vspeedValue = 0.0f;
    float altitude = 0.0025f;
};

#endif