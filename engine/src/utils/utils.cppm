module;
#include <glm/vec2.hpp>
#include <string_view>
export module engine:utils;

export namespace Engine {
    std::string getFile(std::string_view path);

    struct Box {
        glm::vec2 topLeft{0,0};
        glm::vec2 bottomRight{0,0};
    };
}
