module;
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
module engine;

namespace Engine {
    Sprite::Sprite(const glm::vec2 scale_, const glm::vec3 &color, Shader &shader_, const std::vector<float> &vertices_,
                   const std::string_view texturePath) :
        Renderable(0, 0, color, glm::vec2(0, 0), scale_, vertices_, shader_),
        texture(Texture(texturePath, GL_TEXTURE0, "png")) {
        vertices = {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 3.0f, 1.0f, 3.0f, 1.0f, 0.0f, 1.0f, 0.0f};
        for (int i = 0; i < vertices.size(); i += 4) {
            if (boundingBox.topLeft[0] < vertices[i]) {
                boundingBox.topLeft[0] = vertices[i];
            }
            if (boundingBox.topLeft[1] < vertices[i + 1]) {
                boundingBox.topLeft[1] = vertices[i + 1];
            }
            if (boundingBox.bottomRight[0] > vertices[i]) {
                boundingBox.bottomRight[0] = vertices[i];
            }
            if (boundingBox.bottomRight[1] > vertices[i + 1]) {
                boundingBox.bottomRight[1] = vertices[i + 1];
            }
        }
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Sprite::render() const {
        texture.bind();
        shader.use();
        shader.setVec3("objectColor", color);
        shader.setInt("sprite", 0);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }


    Box &Sprite::getBoundingBox() { return boundingBox; }

} // namespace Engine
