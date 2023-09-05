#include <Mathematics.hpp>
#include <cmath>
#include <iostream>


float MATH::calculataVSI(float pitchValue, float speedValue)
{
    float vsIncreaser;

    speedValue = round(-((speedValue - 0.0045) * 40000)) / 100;
    pitchValue = pitchValue * -50;

    if (std::abs(pitchValue) < 0.000001) {
    pitchValue = 0.0f;
    }

    float radyan = pitchValue * M_PI / 180;
    vspeedValue = (speedValue * tan(radyan));


    if (std::abs(vspeedValue) < 0.000001) {
    vspeedValue = 0.0f;
    }

    std::cout << "pitch: " << pitchValue << std::endl;
    std::cout << "VSI: " << vspeedValue << std::endl; 
    std::cout << "Speed: " << (speedValue) << std::endl;

    if(vspeedValue > 25)
    {
        return 25.0f*0.0125;
    }
    else if(vspeedValue < -25)
    {
        return -25.0f*0.0125;
    }
    else
    {
        return vspeedValue*0.0125;
    }

}

float MATH::calculateAltitude(float passingTime)
{  

    altitude -= vspeedValue;
    // altitude = vspeedValue * passingTime;

    
    std::cout <<"altitude: "<< altitude << std::endl;

    return altitude * 0.000025;

}
