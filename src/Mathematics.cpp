#include <Mathematics.hpp>
#include <cmath>
#include <iostream>
float MATH::calculataVSI(float pitchValue, float speedValue)
{
    static float vspeedValue = 0.0;
    float vsIncreaser;
    speedValue = (round(-((speedValue - 0.0045) * 40000)) + 40) / 100;
    pitchValue = pitchValue * -50;


    std::cout << "pitch: " << pitchValue << std::endl;

    float radyan = pitchValue * M_PI / 180;
    vspeedValue = (speedValue * tan(radyan));
    altitude=speedValue/tan(radyan+0.00000001); // formula of altitude 
    std::cout << "VSI: " << vspeedValue << std::endl; 
    std::cout << "Speed: " << (speedValue) << std::endl;
    //upper lower bound 
    if (vspeedValue < 19.9240 && vspeedValue >= 0)
    {
       
        return vspeedValue * 0.0125;
    }
    else if (vspeedValue > 19.9240)
    {
        return 19.924 * 0.0125;
        
    }
    else if (vspeedValue > -20.2007 && vspeedValue <= 0)
    {
        return vspeedValue * 0.0125;
        
    }
    else if (vspeedValue < -20.2007)
    {
        return -1 * 20.20 * 0.0125;
    }
}

float MATH::calculateAltitude(float altiPositions)//now altiposition givin
{    
    //altiPositions = round(-((altiPositions - 0.0025)*40000))+altitude;//TODO design formula according to proper calculation
     std::cout << "altitude: " << (10*altitude/2.5)+115<< std::endl;
    return ((-altitude+1)/10000);
}
