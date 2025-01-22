module;
#include <string>
export module engine:texture;
export namespace Engine {
    class Texture {
    public:
        Texture(std::string_view texturePath, unsigned int textureUnit, const char *imageType);
        [[nodiscard]] unsigned get() const;
        void bind() const;

    private:
        unsigned id, unit;
    };

    unsigned TextureFromFile(const std::string &filename, const std::string &directory, bool gamma = false);
} // namespace Engine
