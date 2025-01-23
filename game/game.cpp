module;
#include <complex>
#include <filesystem>
#include <functional>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
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

        Engine::Shader mainShader({"objectColor", "transpose", "model", "modelNormal", "sprites"},
                                  "../../engine/shaders/main/main.vert", "../../engine/shaders/main/main.frag",
                                  std::nullopt, std::nullopt, std::nullopt);

        Engine::Shader simpleShader({"objectColor", "transpose", "model"},
                                    "../../engine/shaders/simple/simple.vert",
                                    "../../engine/shaders/simple/simple.frag", std::nullopt, std::nullopt,
                                    std::nullopt);

        Engine::Sprite sprite(glm::vec2(10.f, 10.f), glm::vec3(0.0f, 0.0f, 0.0f), mainShader, {},
                              "../../game/resources/textures/sprites/awesomeface.png");
        Engine::Player player(glm::vec2(0, 100), 0, 50.f, {}, 1.0f, sprite);
        Engine::Text coordsText("142", glm::vec3(100, 0, 0), glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        Engine::Text fpsText("fps: 0", glm::vec3(0, 0, 0), glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        Engine::Vectors vectors(glm::vec3(0, 0, 0), mainShader, {0, 0, 100, 100});
        Engine::Rectangle rectangle(sprite.getScale(), glm::vec3(0, 0, 0), simpleShader, sprite.getBoundingBox());

        std::reference_wrapper<Engine::Shader> shaders[] = {std::reference_wrapper(mainShader), std::reference_wrapper(simpleShader)};
        Engine::MainRenderer mainRenderer(shaders, {sprite, rectangle}, player);
        while (!glfwWindowShouldClose(Engine::windows[0])) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Engine::updateTime();
            coordsText.render();
            fpsText.render();
            player.processInput(Engine::windows[0]);
            player.update();
            glm::vec2 pos = player.getPosition();
            rectangle.setPosition(pos);
            mainRenderer.render();
            coordsText.setContent("X: " + std::to_string(pos.x) + " Y: " + std::to_string(pos.y));
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
    catch (std::exception const &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
