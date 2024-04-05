#include "MapCreator.h"

#include <memory>

MapCreator::MapCreator(MainDataRef& data) : _data(data) {};

void MapCreator::calculateTextureSizes(int x, int y) {
    int calibrated_X = x*CELL_SIZE;
    int calibrated_Y = y*CELL_SIZE;

    _data->window.setSize(Vector2u(calibrated_X, calibrated_Y));
    _windowSize = _data->window.getSize();


    //This adjusts the size of the map texture to be 80% of the window size since sidebar takes up 20%
    _mapTexture.create(_windowSize.x*(1-SIDEBAR_RATIO), _windowSize.y*(1-SIDEBAR_RATIO));

    // Set the map area size to the size of the map texture
    mapArea.setSize(Vector2f(_mapTexture.getSize()));

    this->notify("Map texture created, size: " + to_string(_mapTexture.getSize().x) + " by " + to_string(_mapTexture.getSize().y), "System");
}

/**
 * @brief Loads the textures needed for the map creator and scales the background texture to fit the window.
 */
void MapCreator::loadTextures() {
    this->_data->assets.LoadTexture("Game Background", GAME_BG_IMAGE_PATH);
    this->_data->assets.LoadFont("Font", FONT_PATH);
    this->_data->assets.LoadTexture("Wall", WALL_IMAGE_PATH);
    this->_data->assets.LoadTexture("Ogre", OGRE_IMAGE_PATH);
    this->_data->assets.LoadTexture("Skeleton", SKELETON_IMAGE_PATH);
    this->_data->assets.LoadTexture("Player", PLAYER_KNIGHT_IMAGE_PATH);
    this->_data->assets.LoadTexture("Chest", CHEST_IMAGE_PATH);
    this->_data->assets.LoadTexture("Door", DOOR_IMAGE_PATH);
    this->_data->assets.LoadTexture("Lever", LEVER_IMAGE_PATH);
}

/**
 * @brief Initializes the map creator.
 * It first asks the user for the size of the map, then calculates the texture sizes based on the window size.
 * It then loads the textures needed for the map creator and scales the background texture to fit the window.
 * It then initializes the map editing interface and the sidebar.
 */
void MapCreator::Init() {
    Position size=askForSize();
    calculateTextureSizes(size.x, size.y);

    loadTextures();

    // Adjust the view if the window size has been changed
    sf::View view(sf::FloatRect(0, 0, static_cast<float>(size.x * CELL_SIZE), static_cast<float>(size.y * CELL_SIZE)));
    this->_data->window.setView(view);

    _currentMap=make_shared<Map>(size.x, size.y);

    this->mapObserver = MapObserver(_currentMap, &_mapTexture, _data);
    this->mapObserver.attach(this->_data->log);

    _mapTexture.clear(Color::Transparent);

    mapObserver.update();

    initSideBar();
    drawSideBar();

    initButtons();
    drawButtons();

    this->notify("Map creator initialized", "System");


}

void MapCreator::HandleInput() {
    sf::Event event;

    while (this->_data->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                handleCloseEvent();
                break;
            case sf::Event::MouseButtonPressed:
                handleMouseButtonPressedEvent(event);
                break;
            default:
                break; // Handle other events or do nothing
        }
    }
}

void MapCreator::handleCloseEvent() {
    this->_data->window.close();
    this->notify("Window closed", "System");
}

void MapCreator::handleMouseButtonPressedEvent(const sf::Event& event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = this->_data->window.mapPixelToCoords(sf::Mouse::getPosition(this->_data->window));
        processClickActions(mousePos);
    }
}

void MapCreator::processClickActions(const sf::Vector2f& mousePos) {
    if (clearButton.getGlobalBounds().contains(mousePos)) {
        clearMap();

    } else if (saveButton.getGlobalBounds().contains(mousePos)) {
        //TODO save map to file
        saveMapToFile();
    } else if (selectedObject != nullptr && mapArea.getGlobalBounds().contains(mousePos)) {
        placeObjectOnMap(mousePos);

    } else {
        selectObjectFromSidebar(mousePos);
    }
}

void MapCreator::placeObjectOnMap(const sf::Vector2f& mousePos) {

    double notMap=1-SIDEBAR_RATIO;
    int cellX = static_cast<int>(ceil(mousePos.x) / (CELL_SIZE*notMap));
    int cellY = static_cast<int>(ceil(mousePos.y) / (CELL_SIZE*notMap));

    Vector2i pos = {cellX, cellY};

    if (_currentMap->place(selectedObject, pos)) {

        mapObserver.update();
        this->notify("Object placed on map at position (" + to_string(cellX) + ", " + to_string(cellY) + ")", "System");

    }

    else{
        this->notify("Cannot place object at position (" + to_string(cellX) + ", " + to_string(cellY) + ")", "System");
    }
}

void MapCreator::selectObjectFromSidebar(const sf::Vector2f& mousePos) {
    try {
        for (size_t i = 0; i < itemContainers.size(); ++i) {
            if (itemContainers[i].getGlobalBounds().contains(mousePos)) {

                string type = itemNames[i];
                Wall wall;
                wall.textureName = "wall_mid";

                if (type == "Wall") {
                    selectedObject = make_shared<Wall>(wall);
                } //TODO IMPLEMENT OGRE CLASS
                /*else if (type == "Ogre") {
                    selectedObject = make_shared<Ogre>();
                }*/
                else if (type == "Player") {
                    selectedObject = make_shared<Player>(Player());
                } else if (type == "Chest") {
                    selectedObject = make_shared<TreasureChest>(TreasureChest());
                } else if (type == "Door") {
                    selectedObject = make_shared<Door>(Door());
                }

                this->notify("Object selected: " + type, "System");

                isHolding = true;
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in selectObjectFromSidebar: " << e.what() << '\n';
        // Handle exception or recovery
    }
}

void MapCreator::Update(float deltaTime) {}

void MapCreator::Draw(float deltaTime) {

    _mapTexture.clear(Color::Transparent);
    _data->window.clear(Color::Transparent);
    mapObserver.update();

    Texture texture = _mapTexture.getTexture();
    Sprite sprite(texture);
    _data->window.draw(sprite);

    drawSideBar();

    drawButtons();

    _mapTexture.display();
    _data->window.display();
}


/**
 * @brief Initializes the sidebar on the right side of the window with the objects that can be placed on the map.
 */

void MapCreator::clearMap() {
    if (_currentMap) {
        // Reset the map with a new instance
        _currentMap = std::make_shared<Map>(_currentMap->getSizeX(), _currentMap->getSizeY());
        mapObserver.detach(_data->log);

        this->mapObserver = MapObserver(_currentMap, &_mapTexture, _data);

        Draw(0.0f);

        this->notify("Map cleared", "System");
    }

}

void MapCreator::initSideBar() {
    float windowWidth = _windowSize.x;
    float sidebarHeight = _mapTexture.getSize().y; // Sidebar height matches the map texture, not the window
    float sidebarWidth = windowWidth * SIDEBAR_RATIO;
    const float padding = sidebarHeight*SIDEBAR_ITEM_PADDING; // Define padding around sidebar items
    Font font = this->_data->assets.GetFont(FONT_PATH);

    // Predefined colors for readability and consistency
    const sf::Color sidebarColor = sf::Color(50, 50, 50); // Dark gray
    const sf::Color itemContainerColor = sf::Color(70, 70, 70); // Lighter gray for items
    const sf::Color itemContainerOutlineColor = sf::Color(100, 100, 100); // Outline color

    sidebar.setSize(sf::Vector2f(sidebarWidth, sidebarHeight));
    sidebar.setPosition(windowWidth - sidebarWidth, 0);
    sidebar.setFillColor(sidebarColor);

    sidebarObjectsSprites.clear();
    itemContainers.clear();

    float itemHeight = (sidebarHeight - padding * (itemNames.size() + 1)) / itemNames.size();

    float yOffset = padding;

    for (const string& itemName : itemNames) {

        sf::Sprite item(this->_data->assets.GetTexture(itemName));

        // Scale calculation remains the same
        float scaleX = (sidebarWidth * SIDEBAR_ITEM_RATIO) / item.getLocalBounds().width;
        float scaleY = (itemHeight - 2 * padding) / item.getLocalBounds().height; // Consider removing or adjusting this line if it incorrectly calculates scaleY
        float scale = std::min(scaleX, scaleY);
        item.setScale(scale, scale);

        // Center horizontally within the container
        float xPosition = windowWidth - sidebarWidth + (sidebarWidth - item.getLocalBounds().width * scale) / 2;

        // Adjust yPosition to center the item vertically within its container
        // Calculate the actual height of the item after scaling
        float itemActualHeight = item.getLocalBounds().height * scale;
        // Adjust yPosition to center the item vertically within its container
        float yPosition = yOffset + (itemHeight - itemActualHeight) / 2;

        item.setPosition(xPosition, yPosition);

        sf::RectangleShape container(sf::Vector2f(sidebarWidth, itemHeight));
        container.setPosition(windowWidth - sidebarWidth, yOffset);
        container.setFillColor(itemContainerColor);
        container.setOutlineColor(itemContainerOutlineColor);
        container.setOutlineThickness(-1); // Inside outline for a cleaner look

        //TODO CHANGE MAX NUMBER OF SOME ITEMS

        int maxnb=(itemName=="Player"||itemName=="Door")?1:99;

        auto* item_name = const_cast<string *>(&itemName);

        sidebarObjectsSprites.push_back(item);
        itemContainers.push_back(container);

        MapCreator::SidebarItem sidebarObject= SidebarItem(*item_name, maxnb);

        sidebarObjects.push_back(sidebarObject);


        // Move to the next item position, including the padding
        yOffset += itemHeight + padding;
    }
}

void MapCreator::drawSideBar(){
    // Draw the sidebar and its items
    _data->window.draw(sidebar);

    //Draw the rectangles around the items
    for (const auto& container : itemContainers) {
        _data->window.draw(container);
    }

    //Draw the items themselves
    for (const auto& item : sidebarObjectsSprites) {
        _data->window.draw(item);
    }

}

/**
 * @brief Asks the user for the size of the map.
 * @return Size of the map as a Position struct.
 */
Position MapCreator::askForSize() {
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) {
        std::cerr << "Failed to load font." << std::endl;
        return {-1, -1};
    }

    sf::RectangleShape background(sf::Vector2f(this->_data->window.getSize().x, this->_data->window.getSize().y));
    background.setFillColor(sf::Color(50, 50, 50));

    sf::RectangleShape activeIndicator(sf::Vector2f(300.f, 50.f));
    activeIndicator.setFillColor(sf::Color(100, 100, 250, 100));
    activeIndicator.setPosition(10.f, 70.f);

    sf::Text instructionText("Enter map name, Width (X) and Height (Y), then press Enter:", font, 24);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(10.f, 10.f);

    sf::Text mapNameText("Map Name: ", font, 24);
    sf::Text xInputText("Width: ", font, 24);
    sf::Text yInputText("Height: ", font, 24);
    mapNameText.setFillColor(sf::Color::White);
    xInputText.setFillColor(sf::Color::White);
    yInputText.setFillColor(sf::Color::White);
    mapNameText.setPosition(10.f, 80.f);
    xInputText.setPosition(10.f, 130.f);
    yInputText.setPosition(10.f, 180.f);

    std::string mapNameInput = "", xInput = "", yInput = "";
    bool enterPressed = false, focusOnName = true, focusOnX = false, focusOnY = false;

    while (this->_data->window.isOpen()) {
        sf::Event event;
        while (this->_data->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) this->_data->window.close();

            if (!enterPressed && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Backspace
                    if (focusOnName && !mapNameInput.empty()) mapNameInput.pop_back();
                    else if (focusOnX && !xInput.empty()) xInput.pop_back();
                    else if (focusOnY && !yInput.empty()) yInput.pop_back();
                } else if (focusOnName && (event.text.unicode >= 32 && event.text.unicode < 128)) {
                    // Allow any printable character for the map name, including numbers
                    mapNameInput += static_cast<char>(event.text.unicode);
                } else if ((focusOnX || focusOnY) && (event.text.unicode >= '0' && event.text.unicode <= '9')) {
                    // Only allow numeric input for x and y
                    if (focusOnX) xInput += static_cast<char>(event.text.unicode);
                    if (focusOnY) yInput += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == '\r') { // Enter key to switch focus or submit
                    if (focusOnName) {
                        focusOnName = false;
                        focusOnX = true;
                        activeIndicator.setFillColor(sf::Color(100, 250, 100, 100));
                        activeIndicator.setPosition(10.f, 120.f);
                    } else if (focusOnX) {
                        focusOnX = false;
                        focusOnY = true;
                        activeIndicator.setFillColor(sf::Color(250, 100, 100, 100));
                        activeIndicator.setPosition(10.f, 170.f);
                    } else {
                        enterPressed = true;
                    }
                }
            }
        }

        // Drawing section remains the same
        this->_data->window.clear();
        this->_data->window.draw(background);
        this->_data->window.draw(activeIndicator);
        instructionText.setString("Enter map name, Width (X) and Height (Y), then press Enter:");
        mapNameText.setString("Map Name: " + mapNameInput);
        xInputText.setString("Width: " + xInput);
        yInputText.setString("Height: " + yInput);
        this->_data->window.draw(instructionText);
        this->_data->window.draw(mapNameText);
        this->_data->window.draw(xInputText);
        this->_data->window.draw(yInputText);
        this->_data->window.display();

        // Submission and validation logic remains the same
        if (enterPressed) {
            try {
                int width = std::stoi(xInput.empty() ? "0" : xInput);
                int height = std::stoi(yInput.empty() ? "0" : yInput);
                // Ensure map name is not empty and dimensions are within expected range
                if (!mapNameInput.empty() && width > 0 && height > 0 && width <= 50 && height <= 30) {
                    this->mapName = mapNameInput;
                    return {width, height};
                } else {
                    instructionText.setString("Invalid input. Please enter a map name and positive numbers for dimensions.");
                    enterPressed = false;
                    // Reset focus to start correctly after invalid input
                    focusOnName = true;
                    focusOnX = false;
                    focusOnY = false;
                    activeIndicator.setPosition(10.f, 70.f); // Reset position to map name input
                    activeIndicator.setFillColor(sf::Color(100, 100, 250, 100));
                    // Clear inputs for re-entry
                    mapNameInput = "";
                    xInput = "";
                    yInput = "";
                }
            } catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return {-1, -1};
            }
        }
    }

    return {-1, -1};
}

void MapCreator::initButtons() {
    // Button container at the bottom of the window
    float buttonContainerHeight = _windowSize.y*SIDEBAR_RATIO; // Fixed height for button area
    float buttonContainerY = _windowSize.y - buttonContainerHeight; // Positioned at the bottom

    // Container for buttons - helps in positioning and can be used for drawing a background
    sf::RectangleShape buttonContainer(sf::Vector2f(_windowSize.x, buttonContainerHeight));
    buttonContainer.setPosition(0, buttonContainerY);
    buttonContainer.setFillColor(sf::Color(50, 50, 50, 200)); // Semi-transparent dark background

    // Define button dimensions and calculate spacing for centering
    float buttonWidth = _windowSize.x*BOTTOMBAR_BUTTON_WIDTH_RATIO; // Fixed width for buttons
    float buttonHeight = buttonContainerHeight*BOTTOMBAR_BUTTON_HEIGHT_RATIO; // Fixed height for buttons
    float gap = (_windowSize.x - 2 * buttonWidth) / 3; // Space between buttons and window edges

    // Initialize the "Clear" button
    sf::RectangleShape clearButton(sf::Vector2f(buttonWidth, buttonHeight));
    clearButton.setPosition(gap, buttonContainerY + (buttonContainerHeight - buttonHeight) / 2);
    clearButton.setFillColor(sf::Color(100, 100, 100));
    clearButton.setOutlineColor(sf::Color::White); // Add outline for better visibility
    clearButton.setOutlineThickness(1);

    // Initialize the "Save" button
    sf::RectangleShape saveButton(sf::Vector2f(buttonWidth, buttonHeight));
    saveButton.setPosition(2 * gap + buttonWidth, buttonContainerY + (buttonContainerHeight - buttonHeight) / 2);
    saveButton.setFillColor(sf::Color(100, 100, 100));
    saveButton.setOutlineColor(sf::Color::White); // Add outline for better visibility
    saveButton.setOutlineThickness(1);

    // Store buttons for later use in interaction handling
    this->clearButton = clearButton;
    this->saveButton = saveButton;
    this->buttonContainer = buttonContainer;

    // Assuming `_data->assets.GetFont("Font")` is valid and has been loaded earlier
    // Initialize and position the text for "Clear" button
    sf::Text clearButtonText("Clear", this->_data->assets.GetFont("Font"), buttonWidth*0.2);
    clearButtonText.setPosition(
            clearButton.getPosition().x + (buttonWidth - clearButtonText.getLocalBounds().width) / 2,
            clearButton.getPosition().y + (buttonHeight - clearButtonText.getLocalBounds().height) / 2 - 5);

    // Initialize and position the text for "Save" button
    sf::Text saveButtonText("Save", this->_data->assets.GetFont("Font"), buttonWidth*0.2);
    saveButtonText.setPosition(
            saveButton.getPosition().x + (buttonWidth - saveButtonText.getLocalBounds().width) / 2,
            saveButton.getPosition().y + (buttonHeight - saveButtonText.getLocalBounds().height) / 2 - 5);

    // Store button texts for drawing
    this->clearButtonText = clearButtonText;
    this->saveButtonText = saveButtonText;
}

void MapCreator::drawButtons(){
    // Make sure to call this in your main drawing function, after drawing the map and before displaying the window
    _data->window.draw(buttonContainer);
    _data->window.draw(clearButton);
    _data->window.draw(saveButton);

    // Draw text on buttons, ensuring it's centered
    // Assume clearButtonText and saveButtonText have been set up similarly to before, but use draw calls here
    _data->window.draw(clearButtonText);
    _data->window.draw(saveButtonText);
}


MapCreator::SidebarItem::SidebarItem(const string &name, const int permittedCount) {
    this->name = name;
    this->permittedCount = permittedCount;
}

void MapCreator::saveMapToFile() {
    json mapData;
    mapData["name"] = this->mapName;
    mapData["width"] = this->_currentMap->getSizeX();
    mapData["height"] = this->_currentMap->getSizeY();
    mapData["objects"] = json::array();

    for (const auto& row : this->_currentMap->getGrid()) {
        for(const auto& cell : row){
            if (auto wall = dynamic_cast<Wall*>(cell.get())) {
                mapData["objects"].push_back("Wall");
            } else if (auto* player = dynamic_cast<Player*>(cell.get())) {
                mapData["objects"].push_back("Player");
            } else if (auto* item = dynamic_cast<TreasureChest*>(cell.get())) {
                mapData["objects"].push_back("Chest");
            }else if(auto* item=dynamic_cast<Door*>(cell.get())){
                mapData["objects"].push_back("Door");
            }

            else {
                mapData["objects"].push_back(nullptr);
            }
        }
    }

    std::string directory = "../../SavedMaps/";
    std::string filename = directory + this->mapName + ".json";

    // Ensure the directory exists
    std::filesystem::create_directories(directory);

    std::ofstream file(filename, std::ios::out | std::ios::trunc); // Open with truncation mode

    if (file) {
        file << mapData.dump(4);
        file.close();
        this->notify("Map saved to file: " + filename, "System");
    } else {
        // In case of failure, which is unlikely if the directories were correctly created and there are permissions
        this->notify("Failed to save map to file: " + filename, "System");
    }

}
