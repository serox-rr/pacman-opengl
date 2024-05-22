module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <complex>
#include <filesystem>
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <span>
module game;

import engine;

int main() {
    try {
        Engine::init();
        Engine::windows.emplace_back(1920, 1080);
        Engine::windows[0].setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // Engine::windows[0].disableVSYNC();
        Engine::settings();
        int frameAmount = 0;
        double startTime = glfwGetTime();
        Engine::Font inter("../../game/resources/fonts/Inter-VariableFont_slnt,wght.ttf");

        Engine::Shader textShader({"color", "projection"}, "../../engine/shaders/text/text.vert",
                                  "../../engine/shaders/text/text.frag", std::nullopt, std::nullopt, std::nullopt);


        Engine::Text coordsText("142", glm::vec3(100, 0, 0), glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        Engine::Text fpsText("fps: 0", glm::vec3(0, 0, 0), glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        while (!glfwWindowShouldClose(Engine::windows[0])) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Engine::updateTime();
            coordsText.render();
            fpsText.render();
            /*coordsText.setContent("X: " + std::to_string(pos.x) + " Y: " + std::to_string(pos.y) +
                                  " Z: " + std::to_string(pos.z));*/
            glfwSwapBuffers(Engine::windows[0]);
            glfwPollEvents();
            if (glfwGetTime() - startTime > 1.0f) {
                fpsText.setContent("fps: " + std::to_string(frameAmount));
                startTime = glfwGetTime();
                frameAmount = 0;
            }
            frameAmount++;
        }
        glfwTerminate();
    }
    catch (std::exception const&e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
