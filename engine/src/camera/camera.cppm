module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

export module engine:camera;

export namespace Engine {
    class Camera {
    public:
        explicit Camera(glm::vec2 position);

        glm::mat4 &getView();
        [[nodiscard]] double getPitch() const;
        [[nodiscard]] double getYaw() const;
        [[nodiscard]] double getSensitivity() const;
        [[nodiscard]] double getFov() const;
        [[nodiscard]] glm::vec2 getPosition() const;

        virtual void setLookingDirection(float rotation_) = 0;
        virtual void setPosition(glm::vec2 position_) = 0;
        void updateView();
        virtual ~Camera() = default;


    protected:
        glm::vec<2, double> position;
        glm::vec<3, double> front, up;
        glm::mat4 view;
        double yaw, pitch, sensitivity;
    };
} // namespace Engine
