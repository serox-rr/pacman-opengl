module;
#include <glm/glm.hpp>
module engine;

namespace Engine {
    TopCamera::TopCamera(glm::vec2 position) : Camera(position) {

    }
    void TopCamera::setPosition(glm::vec2 position_) { position = position_; }
    void TopCamera::setLookingDirection(float rotation_) {
        updateView();
    }

} // namespace Engine
