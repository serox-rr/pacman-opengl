module;
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
module engine;

namespace Engine {
    MainRenderer::MainRenderer(const std::span<std::reference_wrapper<Shader>> &shaders_,
                               const std::vector<std::shared_ptr<Renderable>> &renderables_,
                               const Player &player_) : Renderer(shaders_, renderables_), player(player_) {}

    void MainRenderer::render() const {
        const Window window = windows[0];
        Camera &camera = player.getActiveCamera();
        const glm::mat4 projection = glm::ortho(static_cast<float>(window.getWidth()), 0.0f,
                                                0.0f, static_cast<float>(window.getHeight()), -10.0f, 10.0f);
        const glm::mat4 transpose = projection * camera.getView();
        std::ranges::for_each(shaders.begin(), shaders.end(), [&transpose](const Shader &shader) {
            shader.use();
            shader.setMat4("transpose", transpose);
        });
        for (const auto& renderable: renderables) {
            process(renderable);
        }
    }

    void MainRenderer::process(const std::shared_ptr<Renderable>& renderable) const {
        const auto &shader = renderable->getShader();
        shader.use();
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(renderable->getPosition(), 0));
        model = glm::scale(model, glm::vec3(renderable->getScale(), 0.f));
        shader.setMat4("model", model);
        shader.setMat3("modelNormal", glm::transpose(glm::inverse(glm::mat3(1.0f))));
        renderable->render();
        for (const auto &child: renderable->getChildren()) {
            child->setScale(renderable->getScale());
            child->setPosition(renderable->getPosition());
            process(child);
        }
    }

} // namespace Engine
