module;
#include <glm/glm.hpp>
#include <vector>
#include <string_view>
export module engine:renderable.sprite;
import :shader;
import :renderable;
import :texture;
import :utils;
export namespace Engine {
    class Sprite final: public Renderable {
    public:
        Sprite(glm::vec2 scale_, const glm::vec3 &color, Shader &shader_, const std::vector<float> &vertices_, std::string_view texturePath);
        void render() const override;
        ~Sprite() override = default;

        [[nodiscard]] Box &getBoundingBox();
    private:
        Texture texture;
        Box boundingBox;
    };
}
