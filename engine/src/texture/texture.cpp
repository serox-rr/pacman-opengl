module;
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>
module engine;


namespace Engine {
    Texture::Texture(const std::string_view texturePath, const unsigned int textureUnit, const char *imageType) : id(0), unit(textureUnit) {
        glGenTextures(1, &id);
        glActiveTexture(unit);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(std::string(texturePath).c_str(), &width, &height, &nrChannels, 0);
        if (!data) {
            throw std::runtime_error("Fichier introuvable !");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, !strcmp(imageType, "jpg") ? GL_RGB : GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    void Texture::bind() const {
        glActiveTexture(unit);
        glBindTexture(GL_TEXTURE_2D, id);
    }


    unsigned Texture::get() const { return id; }

    unsigned TextureFromFile(const std::string &filename, const std::string &directory, bool gamma) {
        auto path = directory + '/' + filename;

        unsigned textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
        if (!data) {
            stbi_image_free(data);
            throw std::runtime_error("Texture failed to load at path: " + std::string(path));
        }
        GLenum format;
        switch (nrComponents) {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                format = GL_RGB;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(format), width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
        return textureID;
    }
} // namespace Engine
