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
        glm::vec2 coordsPos(100,0),fpsPos(0,0), vectorsPos(0,0), spritePos(0,0);
        auto sprite = std::make_shared<Engine::Sprite>(glm::vec2(10,10), spritePos, glm::vec3(0.0f, 0.0f, 0.0f), mainShader, std::vector<float>(),
                              "../../game/resources/textures/sprites/awesomeface.png");
        sprite->addChild<Engine::Rectangle>(sprite->getScale(), sprite->getPosition(), sprite->getColor(), simpleShader, sprite->getBoundingBox());
        Engine::Player player(glm::vec2(0, 100), 0, 50.f, {}, 1.0f, sprite);
        Engine::Text coordsText("142", coordsPos, glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        Engine::Text fpsText("fps: 0", fpsPos, glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        Engine::Box box({0,0},{10,10});
        auto rectangle = std::make_shared<Engine::Rectangle>(glm::vec2(10,10), fpsPos, glm::vec3(100,100,0), simpleShader, box);
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
