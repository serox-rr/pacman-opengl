module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
module engine;


namespace Engine {
    Camera::Camera(const glm::vec2 _position) :
        position(_position), front(glm::vec3(0.0, 0.0, -1)), up(glm::vec3(0.0, 1.0, 0.0)),
        view(glm::lookAt(glm::vec<3, double>(position.x, position.y, 0),
                         glm::vec<3, double>(position.x, position.y, 0) + front, up)),
        yaw(-90.0), pitch(0.0), sensitivity(0.1) {}

    glm::mat4 &Camera::getView() { return view; }

    void Camera::updateView() {
        view = glm::lookAt(glm::vec<3, double>(position.x, position.y, 0),
                           glm::vec<3, double>(position.x, position.y, 0) + front, up);
    }

    double Camera::getPitch() const { return pitch; }

    double Camera::getYaw() const { return yaw; }

    double Camera::getSensitivity() const { return sensitivity; }

    glm::vec2 Camera::getPosition() const { return position; }
} // namespace Engine
