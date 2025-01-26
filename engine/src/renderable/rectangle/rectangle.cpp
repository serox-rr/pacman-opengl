module;
#include <FastNoise/FastNoise.h>
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
module engine;

namespace Engine {
    Rectangle::Rectangle(Shader &shader_, Box &box_) : Rectangle(glm::vec2(0,0), glm::vec2(0,0), glm::vec3(0,0,0), shader_, box_) {}
    Rectangle::Rectangle(const glm::vec2& scale_, const glm::vec2& position_, const glm::vec3 &color, Shader &shader_, Box &box_) :
        Renderable(0, 0, color, position_, scale_,
                   {box_.topLeft[0], box_.topLeft[1], box_.topLeft[0], box_.bottomRight[1], box_.bottomRight[0],
                    box_.bottomRight[1], box_.bottomRight[0], box_.topLeft[1]},
                   shader_), box(box_) {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }

    void Rectangle::render() const {
        shader.use();
        shader.setVec3("objectColor", color);
        glBindVertexArray(vao);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

    Rectangle::~Rectangle() = default;

} // namespace Engine
