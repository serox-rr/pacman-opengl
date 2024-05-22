module;
#include <memory>
export module engine;
export import :utils;
export import :camera;
export import :shader;
export import :texture;
export import :window;
export import :font;
export import :exception;
export import :renderer;
export import :renderer.main;
export import :renderable;
export import :renderable.text;
export import :renderable.vectors;
export import :renderable.points;
export import :renderable.model;
export import :renderable.mesh;
export import :entity;
export import :entity.player;

export namespace Engine {
    void init();
    void settings();
    void updateTime();

    std::vector<Window> windows({});
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    std::unique_ptr<Points> points;
}
