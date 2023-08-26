#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "landscape.hpp"
#include "AttitudeIndicator.hpp"
#include "aircraft.hpp"
#include "altimeter.hpp"
#include "SpeedIndicator.hpp"
#include "UserInterface.hpp"
#include <iostream>
//constants for moving
float circleYPositions = 0.0f;
float circleRotations = 0.0f;
float slipSkidAmount = 0.0f;
float YPositions =0.4619f;// starting position
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                circleYPositions -= 0.01f;
                break;
            case GLFW_KEY_S:
               circleYPositions += 0.01f;
                break;
             case GLFW_KEY_UP:
             if(YPositions!=0.4619f)//lower bound
                YPositions+=0.001f;
                break;
            case GLFW_KEY_DOWN:
                if(YPositions>=-0.463095f)//upper bound
                 YPositions-=0.001f;
                 std::cout<<YPositions<<std::endl;
                break;
            case GLFW_KEY_Q:
                circleRotations -= 0.5f;
                break;
            case GLFW_KEY_E:
                circleRotations += 0.5f;
                break;
            case GLFW_KEY_Z:
                slipSkidAmount -= 0.001f;
                break;
            case GLFW_KEY_X:
               slipSkidAmount += 0.001f;
                break;
           
            default:
                break;
        }
    }
}


int main() {
    // GLFW'yi başlat
    if (!glfwInit()) {
        return -1;
    }

    // GLFW'yi OpenGL ES 2.0 ile kullanacak şekilde yapılandır
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Pencere oluştur
    GLFWwindow* window = glfwCreateWindow(800, 800, "PFD Screen", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
//
    // OpenGL bağlamını ayarla
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    Landscape landscape;
    AttitudeIndicator ai;
    Aircraft aircraft;
    Altimeter alti;
    SpeedIndicator speedindicator;
    UserInterface ui;



    // Sonsuz döngüyü başlat
    while (!glfwWindowShouldClose(window)) {
        // Renk tamponunu temizle (mavi)
        glClearColor(0.0f, 0.541f, 0.816f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        landscape.Draw(circleYPositions, circleRotations);
        //ai.Draw(circleYPositions, circleRotations, slipSkidAmount);
        aircraft.Draw();
        

        // //blend for texture transparency
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      
        alti.Draw(YPositions);
        speedindicator.Draw(YPositions);
        ui.Draw();
        glDisable(GL_BLEND);

        ai.Draw(circleYPositions, circleRotations, slipSkidAmount);
        
        // Pencere ön yüzeyini güncelle
        glfwSwapBuffers(window);

        // Olayları işle
        glfwPollEvents();
    }

    // GLFW'yi temizle
    glfwTerminate();
    return 0;
}
