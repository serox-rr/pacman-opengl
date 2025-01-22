module;
#include <any>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <span>

export module engine:entity;
import :renderable;
import :renderable.sprite;
export namespace Engine {
    class Entity {
    public:
        Entity(glm::vec2 position_, float rotation_, double speed_, const std::initializer_list<std::reference_wrapper<const Renderable>> &collidables_, float mass_, Sprite &sprite_);
        virtual void update() = 0;
        void setLookingDirection(float rotation_);
        void setSpeed(float _speed);
        [[nodiscard]] float getRotation() const;
        [[nodiscard]] glm::vec2 getPosition() const;
        Sprite &getSprite() const;
        virtual ~Entity() = default;
        glm::vec3 front, up;
    protected:
        glm::vec2 position, travelVelocity;
        float rotation, mass, speed;
        std::vector<std::reference_wrapper<const Renderable>> collidables;
        Sprite &sprite;
    };
} // namespace Engine
