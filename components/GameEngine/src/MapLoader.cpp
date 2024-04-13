/**
* @file MapCreator.h
* @author Ricardo Raji Chahine 40234410
* @brief This class is called from the main menu and allows the user to create a map by placing objects on a grid and then either save or clear that map.
* @brief The user can place walls, doors, levers, chests, characterList, and npcs on the map.
* @brief The maps are saved as .json files in the Saved Maps directory.
*/
#include "MapLoader.h"

#include <memory>

MapLoader::MapLoader(MainDataRef& data) : _data(data) {};

void MapLoader::Init() {
        this->_data->assets.LoadTexture("Menu Background", MENU_BG_IMAGE_PATH);
        this->_data->assets.LoadFont("Font", FONT_PATH);
        _bg.setTexture(this->_data->assets.GetTexture("Menu Background"));
        _bg.setTextureRect(sf::IntRect(0, 0, this->_data->window.getSize().x, this->_data->window.getSize().y));

        vector<std::string> files = listSavedMaps();
        int choice = getUserSelection(files);
        this->notify("Going back to main menu", "System");
        _data->stateMachine.RemoveState();

}



void MapLoader::loadMapFromFile(const std::string& filename) {
    std::string path = "../../SavedMaps/" + filename;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << path << std::endl;
        return;
    }

    nlohmann::json mapData;
    file >> mapData;
    file.close();

}


std::vector<std::string> MapLoader::listSavedMaps() {
    std::vector<std::string> files;
    std::string path = "../../SavedMaps/";
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

int MapLoader::getUserSelection(const std::vector<std::string>& files) {
    int selected = -1;
    Font& font = _data->assets.GetFont("Font");

    if (!font.loadFromFile(FONT_PATH)) {
        std::cerr << "Failed to load font." << std::endl;
        return -1;
    }

    sf::Text menuText;
    menuText.setFont(font);
    menuText.setCharacterSize(24);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition(50, 50);

    std::string menuContent;
    for (size_t i = 0; i < files.size(); ++i) {
        menuContent += std::to_string(i + 1) + ". " + files[i] + "\n";
    }
    menuText.setString(menuContent);

    while (_data->window.isOpen()) {
        sf::Event event;
        while (_data->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _data->window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num0) {
                    DisplayCreationMessage("The map is loaded. You have to run the program again.");
                    return -1;  // Return -1 to indicate no map was selected
                }

            }
        }
        _data->window.clear();
        _data->window.draw(menuText);
        _data->window.display();
    }
    return selected;
}

void MapLoader::DisplayCreationMessage(const std::string& message) {
    // Set up a text object to display the message
    sf::Text creationMessage;
    creationMessage.setFont(_data->assets.GetFont("My Font"));
    creationMessage.setString(message);
    creationMessage.setCharacterSize(MENU_CHAR_SIZE); // Use the same size as your menu items for consistency
    creationMessage.setFillColor(sf::Color::White);

    // Center the message on the screen
    sf::FloatRect messageBounds = creationMessage.getLocalBounds();
    creationMessage.setOrigin(messageBounds.width / 2, messageBounds.height / 2);
    creationMessage.setPosition(_data->window.getSize().x / 2.0f, _data->window.getSize().y / 2.0f);

    // Draw the message
    _data->window.clear();
    _data->window.draw(_bg); // Draw the background first
    _data->window.draw(creationMessage); // Draw the message on top
    _data->window.display();

    // Wait for a short time to display the message
    sf::sleep(sf::seconds(2)); // For example, wait for 1.5 seconds
}



void MapLoader::HandleInput(){}

void MapLoader::Update(float deltaTime){}

void MapLoader::Draw(float deltaTime) {}


/**
 * @brief Calculates the size of the map texture based on the Input from the user.
 * @param x Width of the map.
 * @param y Height of the map.
 */


