module;
#include <GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <optional>
module engine;

namespace Engine {
    Player::Player(const glm::vec2 &position_, const float rotation_, const double speed_,
                   const std::initializer_list<std::reference_wrapper<const Renderable>> &collidables_,
                   const float mass_, Sprite &sprite_) :
        Entity(position_, rotation_, speed_, collidables_, mass_, sprite_), lastMouseX(windows[0].getWidth() / 2),
        lastMouseY(windows[0].getHeight() / 2), firstMouse(true),
        keyStates({{GLFW_KEY_V, false}, {GLFW_KEY_SPACE, false}}) {
        cameras.push_back(std::make_shared<TopCamera>(position_));
        activeCamera = cameras[0];
        processInput(windows[0]);
        static auto mouseCallbackStatic = [this](GLFWwindow *window, const double xpos, const double ypos) {
            mouse_callback(window, xpos, ypos);
        };
        glfwSetCursorPosCallback(windows[0], [](GLFWwindow *window, const double xpos, const double ypos) {
            mouseCallbackStatic(window, xpos, ypos);
        });
    }

    void Player::update() {
        auto tposition = travelVelocity * deltaTime + position;
        position = tposition;
        sprite.setPosition(position);
        activeCamera->setPosition(position - glm::vec2(windows[0].getWidth()/2,windows[0].getHeight()/2));
        activeCamera->setLookingDirection(rotation);
    }

    std::optional<bool> Player::toggleInput(GLFWwindow *window, const unsigned input) {
        if (glfwGetKey(window, input) == GLFW_PRESS && !keyStates[input])
            return keyStates[input] = true;
        if (glfwGetKey(window, input) == GLFW_RELEASE && keyStates[input])
            return keyStates[input] = false;
        return std::nullopt;
    }

    void Player::processInput(GLFWwindow *window) {
        travelVelocity = glm::vec3(0, 0, 0);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            travelVelocity += glm::vec2(0, 1) * speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            travelVelocity += glm::vec2(0, -1) * speed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            travelVelocity += glm::vec2(1, 0) * speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            travelVelocity += glm::vec2(-1, 0) * speed;
        if (const auto key = toggleInput(window, GLFW_KEY_V); key.has_value() && key.value()) {
            activeCamera = cameras[cameras[0] == activeCamera];
        }
        /*setSpeed(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 500 : 3.5);*/
    }


    void Player::mouse_callback(GLFWwindow *window, const double xpos, const double ypos) {
        /*float xoffset = xpos - lastMouseX;
        float yoffset = lastMouseY - ypos; // reversed since y-coordinates range from bottom to top
        lastMouseX = xpos;
        lastMouseY = ypos;
        if (firstMouse) // initially set to true
        {
            lastMouseX = xpos;
            lastMouseY = ypos;
            firstMouse = false;
        }
        xoffset *= activeCamera->getSensitivity();
        yoffset *= activeCamera->getSensitivity();
        setLookingDirection(rotation);*/
    }

    Camera &Player::getActiveCamera() const { return *activeCamera; }
} // namespace Engine
