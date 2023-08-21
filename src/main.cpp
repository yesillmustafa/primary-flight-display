#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "landscape.hpp"
#include "AttitudeIndicator.hpp"
#include "aircraft.hpp"


float circleYPositions = 0.0f;
float circleRotations = 0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                circleYPositions -= 0.01f;
                break;
            case GLFW_KEY_S:
               circleYPositions += 0.01f;
                break;
             case GLFW_KEY_A:
                
                break;
            case GLFW_KEY_D:
                
                break;
            case GLFW_KEY_Q:
                circleRotations += 0.4f;
                break;
            case GLFW_KEY_E:
                circleRotations -= 0.4f;
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

    // OpenGL bağlamını ayarla
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    Landscape landscape;
    AttitudeIndicator ai;
    Aircraft aircraft;

    // Sonsuz döngüyü başlat
    while (!glfwWindowShouldClose(window)) {
        // Renk tamponunu temizle (mavi)
        glClearColor(0.0f, 0.541f, 0.816f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        landscape.Draw(circleYPositions, circleRotations);
        ai.Draw(circleYPositions, circleRotations);
        aircraft.Draw();

        // Pencere ön yüzeyini güncelle
        glfwSwapBuffers(window);

        // Olayları işle
        glfwPollEvents();
    }

    // GLFW'yi temizle
    glfwTerminate();
    return 0;
}
