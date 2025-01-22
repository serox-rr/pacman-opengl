module;
#include <glm/glm.hpp>
export module engine:camera.top;
import :camera;

export namespace Engine {
    class TopCamera final : public Camera {
    public:
        explicit TopCamera(glm::vec2 position);
        void setPosition(glm::vec2 position_) override;
        void setLookingDirection(float rotation_) override;
        ~TopCamera() override = default;
    };
} // namespace Engine
