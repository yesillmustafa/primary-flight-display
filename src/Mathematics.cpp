#include <Mathematics.hpp>
#include <cmath>
#include <iostream>


float MATH::calculataVSI(float pitchValue, float speedValue)
{
    float vsIncreaser;

    speedValue = round(-((speedValue - 0.0045) * 40000)) / 100;
    hspeedValue+=speedValue;
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

    
    std::cout <<"altitude: "<< -1*(((altitude * 0.000025)/2.0)*100000) << std::endl;

    return altitude * 0.00003025;

}


float MATH::calculateRadyan( )
{  

   
    // Adım 1: Dikey ve yatay hızları girin
    double Vd=vspeedValue*0.0125, Vy=hspeedValue;
    /*cout << "Dikey hiz (Vd): ";
    cin >> Vd;
    cout << "Yatay hiz (Vy): ";
    cin >> Vy;*/

    // Adım 2: Altimetre değerini girdikten sonra uygun birimlere dönüştürün
    double altimetreFeet=altitude * 0.00003025; ;
    /*cout << "Altimetre degeri (feet): ";
    cin >> altimetreFeet;*/
    double R = (altimetreFeet / 60) * 0.3048;

    // Adım 3: Manyetik kuzey açısını girdikten sonra radyan cinsine dönüştürün
    double manyetikKuzey=R; //adana için 2018 manyetik kuzey
   /* cout << "Manyetik kuzey acisi (radyan): ";
    cin >> manyetikKuzey;*/

    // Adım 4: Pusula yönünü hesapla
    double pusulaYonu = atan2(Vy, Vd);
    float gercekPusulaYonu = manyetikKuzey + pusulaYonu;
     std::cout << "Gercek Pusula Yonu (radyan): " << 100000*gercekPusulaYonu << std::endl;
    return -100000*gercekPusulaYonu;
    // Sonucu ekrana yazdırın

}

