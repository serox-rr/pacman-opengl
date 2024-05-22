module;

export module engine:renderer.main;
import :renderer;
import :entity.player;

export namespace Engine {
    class MainRenderer final: public Renderer<Renderable> {
    public:
        MainRenderer(const std::span<std::reference_wrapper<Shader>> &shaders_,
                               const std::vector<std::reference_wrapper<Renderable>> &renderables_, const Player &player_);
        void render() const override;
        ~MainRenderer() override = default;
    private:
        const Player &player;
    };
}
