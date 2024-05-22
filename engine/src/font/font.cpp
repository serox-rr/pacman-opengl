module;
#include <iostream>
#include <stdexcept>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
module engine;

namespace Engine {
    Font::Font(const std::string&_path): characters({}), path(_path) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            throw FreetypeError(FreetypeErrorCodes::LIBRARY_LOADING);
        FT_Face face;
        if (FT_New_Face(ft, path.c_str(), 0, &face)) //../../../engine/fonts/Inter-VariableFont_slnt,wght.ttf
            throw FreetypeError(FreetypeErrorCodes::FONT_LOADING);
        FT_Set_Pixel_Sizes(face, 0, 48);
        if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
            throw FreetypeError(FreetypeErrorCodes::GLYPH_LOADING);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                throw FreetypeError(FreetypeErrorCodes::GLYPH_LOADING);
            }
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            characters.insert(std::pair<char, Character>(c, character));
        }
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    std::map<char, Character>& Font::getCharacters() {
        return characters;
    }
}
