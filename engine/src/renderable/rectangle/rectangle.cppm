module;
#include <glm/glm.hpp>
#include <vector>
export module engine:renderable.rectangle;
import :shader;
import :renderable;
import :utils;
export namespace Engine {
    struct Box;
    class Rectangle final: public Renderable {
    public:
        explicit Rectangle(glm::vec2 scale_, const glm::vec3 &color, Shader &shader_, Box &box_);
        void render() const override;
        ~Rectangle() override;

        void setBox(const Box &box_) const {
            box = box_;
        }
    private:
        Box &box;
    };
}
