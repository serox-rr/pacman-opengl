module;
#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
module engine;

namespace Engine {
    MainRenderer::MainRenderer(const std::span<std::reference_wrapper<Shader>> &shaders_,
                               const std::vector<std::reference_wrapper<Renderable>> &renderables_, const Player &player_) :
        Renderer(shaders_, renderables_), player(player_) {}

    void MainRenderer::render() const {
        const Window window = windows[0];
        Camera &camera = player.getActiveCamera();
        const glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window.getWidth()),
                                                static_cast<float>(window.getHeight()), 0.0f, -1.0f, 1.0f);
        const glm::mat4 transpose = projection * camera.getView();
        std::ranges::for_each(shaders.begin(), shaders.end(), [&transpose](Shader &shader) {
            shader.use();
            shader.setMat4("transpose", transpose);
            shader.addUniforms({"light.direction", "light.ambient", "light.diffuse", "light.specular"});
            shader.setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
            shader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
            shader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
            shader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        });
        std::ranges::for_each(renderables.begin(), renderables.end(), [](const Renderable &renderable) {
            const auto shader = renderable.getShader();
            shader.use();
            shader.setMat4("model", glm::translate(glm::mat4(1.0f), renderable.getPosition()));
            shader.setMat3("modelNormal", glm::transpose(glm::inverse(glm::mat3(1.0f))));
            renderable.render();
        });
    }
} // namespace Engine
