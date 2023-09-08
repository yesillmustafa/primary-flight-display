#include <Mathematics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>

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

      double num = altitude;
    
    std::ostringstream ss;
    ss << std::fixed << num;
    
    std::string complicatedNumber = ss.str();
    

    complicatedNumber = complicatedNumber.substr(0, complicatedNumber.find('.') + 9); 
    
    
   float convFloat = std::stof(complicatedNumber);
    
    std::cout <<"altitude: "<< -1*(((altitude * 0.000025)/2.0)*100000) << std::endl;


    if(convFloat>=0.0025f)
    return  (0.0027);
    else
    return(altitude * 0.00003025);

}


float MATH::calculateRadyan(float speed,float rotationValue)
{  
    if(speed == 0.0045f)
    {
        speed = 0.0f;
    }

    speedValue = speed;
    std::cout << "rotation: "<< rotationValue << std::endl;
    direction -= speedValue * (rotationValue / 100);
    // Yeni değeri 0 ila 360 derece aralığında tut
    if (direction < 0.0f)
    {
        direction += 360.0f;
    }
    else if (direction >= 360.0f)
    {
        direction -= 360.0f;
    }
    std::cout << "direction: " << direction << std::endl;

    return direction;
   
}

