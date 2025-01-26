module;
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>
export module engine:entity.player;
import :camera;
import :entity;
export namespace Engine {
    class Player final : public Entity {
    public:
        Player(const glm::vec2 &position_, float rotation_, double speed_, const std::initializer_list<std::reference_wrapper<const Renderable>>& collidables_, float mass_, std::shared_ptr<Sprite> sprite_);
        void update() override;
        void mouse_callback(GLFWwindow *window, double xpos, double ypos);
        void processInput(GLFWwindow *window);
        std::optional<bool> toggleInput(GLFWwindow *window, unsigned input);
        [[nodiscard]] Camera &getActiveCamera() const;
        ~Player() override = default;

    private:
        std::vector<std::shared_ptr<Camera>> cameras;
        std::shared_ptr<Camera> activeCamera;
        float lastMouseX, lastMouseY;
        bool firstMouse;
        std::map<unsigned, bool> keyStates;
    };
} // namespace Engine
