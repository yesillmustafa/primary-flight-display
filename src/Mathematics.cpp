#include <Mathematics.hpp>
#include <cmath>
#include <iostream>
float MATH::calculataVSI(float pitchValue, float speedValue)
{
    static float vspeedValue=0.0;
    float vsIncreaser;
    speedValue = (round(-((speedValue - 0.0045) * 40000)) + 40) / 100;
    pitchValue = pitchValue * -52;
   // std::cout<<pitchValue<<std::endl;
    float radyan = pitchValue* M_PI / 180;

   
  
        vspeedValue = (speedValue * tan(radyan));
   
     //std::cout << vspeedValue << std::endl;
    return vspeedValue/100;
}

float MATH::calculateAltitude(float altiPositions )
{
     std::cout <<  round(-((altiPositions - 0.0025)*40000))<< std::endl;
    return altiPositions;
    
}
