/**
 * @file AssetManager.h
 * @brief This file contains the declaration of the AssetManager class.
 *        AssetManager is responsible for loading and managing game assets such as textures and fonts.
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 */

#ifndef A2_ASSETMANAGER_H
#define A2_ASSETMANAGER_H

#include "Log/include/LogObservable.h"
#include "SFML/Graphics.hpp"
#include <map>
using namespace std;
using namespace sf;

/**
 * @class AssetManager
 * @brief The AssetManager class is responsible for loading and managing game assets such as textures and fonts.
 *        It inherits from LogObservable to provide logging functionality.
 */
class AssetManager : public LogObservable {
public:
    /**
     * @brief Default constructor for AssetManager.
     */
    AssetManager() = default;

    /**
     * @brief Default destructor for AssetManager.
     */
    ~AssetManager() override = default;

    /**
     * @brief Loads a texture from a file and associates it with a name.
     * @param name The name to associate with the loaded texture.
     * @param filename The path to the file containing the texture.
     */
    void LoadTexture(const string &name, const string &filename);

    /**
     * @brief Retrieves a texture associated with a given name.
     * @param name The name of the texture to retrieve.
     * @return A reference to the requested texture.
     */
    Texture &GetTexture(const string &name);

    /**
     * @brief Loads a font from a file and associates it with a name.
     * @param name The name to associate with the loaded font.
     * @param filename The path to the file containing the font.
     */
    void LoadFont(const string &name, const string &filename);

    /**
     * @brief Retrieves a font associated with a given name.
     * @param name The name of the font to retrieve.
     * @return A reference to the requested font.
     */
    Font &GetFont(const string &name);

private:
    map<string, Texture> _textures;///< Map to store loaded textures.
    map<string, Font> _fonts;      ///< Map to store loaded fonts.
};

#endif//A2_ASSETMANAGER_H
