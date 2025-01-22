module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
module engine;

namespace Engine {
    Entity::Entity(glm::vec2 position_, float rotation_, double speed_,
                   const std::initializer_list<std::reference_wrapper<const Renderable>> &collidables_, float mass_,
                   Sprite &sprite_) :
        position(position_), rotation(rotation_), travelVelocity(0, 0), front(0.0, 0.0, -1.0),
        up(0.0, 1.0, 0.0), mass(mass_), speed(speed_), collidables(collidables_),
        sprite(sprite_) {}

    void Entity::setLookingDirection(const float rotation_) {
        rotation = fmod(rotation_, 360.f);
        glm::vec3 direction;
        direction.x = cos(rotation);
        direction.x = sin(rotation);
        front = glm::normalize(direction);
    }

    void Entity::setSpeed(const float _speed) { speed = _speed; }

    float Entity::getRotation() const { return rotation; }

    glm::vec2 Entity::getPosition() const { return position; }

    Sprite &Entity::getSprite() const { return sprite; }

} // namespace Engine
