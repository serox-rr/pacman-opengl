module;
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
export module engine:renderable;
import :shader;
export namespace Engine {
    class Renderable {
    public:
        Renderable(const unsigned vao, const unsigned vbo, const glm::vec3 &color_, const glm::vec2 position_,
                   const glm::vec2 scale_, const std::vector<float> &vertices_, Shader &shader_) :
            vao(vao), vbo(vbo), color(color_), position(position_), scale(scale_), shader(shader_),
            vertices(vertices_) {};
        virtual void render() const = 0;
        virtual ~Renderable() = default;
        [[nodiscard]] glm::vec3 getColor() const { return color; }

        void setColor(const glm::vec3 &color_) { color = color_; }

        void setPosition(const glm::vec2 &position_) { position = position_; }

        void setScale(const glm::vec2 &scale_) { scale = scale_; }

        void setVertices(const std::vector<float> &vertices_) {
            vertices = vertices_;
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
        }

        [[nodiscard]] glm::vec2 getPosition() const { return position; }

        [[nodiscard]] const Shader &getShader() const { return shader; }

        [[nodiscard]] std::vector<float> getVertices() const { return vertices; }

        [[nodiscard]] glm::vec2 getScale() const { return scale; }

    protected:
        unsigned vao, vbo;
        glm::vec3 color;
        glm::vec2 position, scale;
        Shader &shader;
        std::vector<float> vertices;
    };

} // namespace Engine
