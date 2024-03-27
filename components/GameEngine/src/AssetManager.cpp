/**
 * @file AssetManager.cpp
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#include "AssetManager.h"
#include <memory>


void AssetManager::LoadTexture( const std::string& name,  const std::string& filename) {
    Texture tex;

    // Checks if texture is already loaded
    if (_textures.find(name) != _textures.end()) {
        return;
    }

    if (tex.loadFromFile(filename)){
        _textures[name] = tex;
        this->notify("Texture loaded: " + name, "System");
    }
}

Texture &AssetManager::GetTexture( const std::string& name) {
    return _textures[name];
}


void AssetManager::LoadFont( const std::string& name,  const std::string& filename) {
    Font font;

    // Checks if font is already loaded
    if (_fonts.find(name) != _fonts.end()) {
        return;
    }

    if (font.loadFromFile(filename)){
        _fonts[name] = font;
    }
}

Font &AssetManager::GetFont( const std::string& name) {
    return this->_fonts[name];
}
