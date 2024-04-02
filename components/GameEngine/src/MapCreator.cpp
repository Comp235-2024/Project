#include "MapCreator.h"

MapCreator::MapCreator(MainDataRef& data) : _data(data) {};

void MapCreator::calculateTextureSizes(int x, int y) {
    int calibrated_X = x*CELL_SIZE;
    int calibrated_Y = y*CELL_SIZE;

    _data->window.setSize(Vector2u(calibrated_X, calibrated_Y));
    _windowSize = _data->window.getSize();

    // TODO make the console and character view sizes dynamic
    _mapTexture.create(_windowSize.x, _windowSize.y);
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
    this->_data->assets.LoadTexture("Chest", CHEST_IMAGE_PATH);
    this->_data->assets.LoadTexture("Door", DOOR_IMAGE_PATH);

    // Setting up the background texture
    _bg.setTexture(this->_data->assets.GetTexture("Game Background"));
    // Ensure the texture covers the entire window; this might involve scaling
    _bg.setScale(
            float(_data->window.getSize().x) / _bg.getTexture()->getSize().x,
            float(_data->window.getSize().y) / _bg.getTexture()->getSize().y
    );
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

    initMapEditingInterface();

}

void MapCreator::HandleInput() {
    Event event{};
    while (this->_data->window.pollEvent(event)) {
        if (Event::Closed == event.type) {
            this->_data->window.close();
            this->notify("Window closed", "System");
        }

        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(_data->window);
                if (sidebar.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    for (auto& object : sidebarObjects) {
                        if (object.sprite.getGlobalBounds().contains(mousePos.x, mousePos.y) && object.nbPremitted > 0) {
                            selectedObject = &object;
                            break;
                        }
                    }
                } else if (mapArea.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (selectedObject != nullptr) {
                        PlaceableObject newObject=*selectedObject;
                        Position position = {mousePos.x, mousePos.y};

                        cout<<"Placing object of type: "<<newObject.type<<" at position: "<<position.x<<", "<<position.y<<endl;
                        //_currentMap->place(newObject, position);
                    }
                }

                selectedObject= nullptr;
            }
        }


    }
}

void MapCreator::Update(float deltaTime) {}

void MapCreator::Draw(float deltaTime) {
    initMapEditingInterface();
    _data->window.clear();
    _data->window.draw(_bg);
    _data->window.draw(sidebar);

    Texture texture = _mapTexture.getTexture();
    Sprite mapSprite(texture);
    _data->window.draw(mapSprite);
    _data->window.display();
}

void MapCreator::initMapEditingInterface() {

    _mapTexture.clear(Color::Transparent);
    _mapTexture.draw(_bg);

    initSideBar();

    _mapTexture.display();
}

void MapCreator::initSideBar() {
    float windowWidth = this->_data->window.getSize().x;
    float windowHeight = this->_data->window.getSize().y;
    float sidebarWidth = windowWidth * SIDEBAR_RATIO;

    sidebar.setSize(sf::Vector2f(sidebarWidth, windowHeight));
    sidebar.setPosition(windowWidth - sidebarWidth, 0);
    sidebar.setFillColor(sf::Color(50, 50, 50)); // Dark gray

    sidebarObjectsSprites.clear();
    itemContainers.clear();

    std::vector<std::string> itemNames = {"Wall", "Ogre", "Chest", "Door"};
    float totalSpacing = windowHeight * 0.05; // Total vertical spacing to distribute
    float itemHeight = (windowHeight - totalSpacing) / itemNames.size(); // Even height for each item

    float yOffset = totalSpacing / itemNames.size(); // Initial offset from top for spacing

    for (const auto& itemName : itemNames) {
        sf::Sprite item(this->_data->assets.GetTexture(itemName));

        // Calculate scale to maintain aspect ratio and fit within the allocated width and height
        float originalWidth = item.getLocalBounds().width;
        float originalHeight = item.getLocalBounds().height;
        float scaleX = (sidebarWidth * SIDEBAR_ITEM_RATIO) / originalWidth;
        float scaleY = itemHeight / originalHeight;
        float scale = std::min(scaleX, scaleY); // Ensure the item fits within its container

        item.setScale(scale, scale);

        // Calculate horizontal and vertical position to center item within its allocated space
        float xPosition = windowWidth - sidebarWidth + (sidebarWidth - originalWidth * scale) / 2;
        float yPosition = yOffset + (itemHeight - originalHeight * scale) / 2; // Center vertically within the container
        item.setPosition(xPosition, yPosition);

        sf::RectangleShape container(sf::Vector2f(sidebarWidth, itemHeight));
        container.setPosition(windowWidth - sidebarWidth, yOffset);
        container.setFillColor(sf::Color(70, 70, 70)); // Slightly lighter gray for contrast
        container.setOutlineColor(sf::Color(100, 100, 100));
        container.setOutlineThickness(-1); // Outline inside for cleaner look

        sidebarObjectsSprites.push_back(item);
        itemContainers.push_back(container);

        yOffset += itemHeight; // Move yOffset to the next item's position
    }

    // Draw the sidebar and its items
    _mapTexture.draw(sidebar);
    for (const auto& container : itemContainers) {
        _mapTexture.draw(container);
    }
    for (const auto& item : sidebarObjectsSprites) {
        _mapTexture.draw(item);
    }
}



/**
 * @brief Asks the user for the size of the map.
 * @return Size of the map as a Position struct.
 */
Position MapCreator::askForSize() {
    // Load a font for text display
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) {
        std::cerr << "Failed to load font." << std::endl;
        return {-1, -1}; // Return an error position if the font can't be loaded
    }

    // Setting up the visual elements for UI
    // Background for the input UI
    sf::RectangleShape background(sf::Vector2f(this->_data->window.getSize().x, this->_data->window.getSize().y));
    background.setFillColor(sf::Color(50, 50, 50)); // Dark gray color for contrast

    // Active input field indicator to show which field (width/height) is active
    sf::RectangleShape activeIndicator(sf::Vector2f(300.f, 50.f)); // Size and initial color for width input
    activeIndicator.setFillColor(sf::Color(100, 100, 250, 100)); // Semi-transparent blue
    activeIndicator.setPosition(10.f, 70.f); // Position it near the width input initially

    // Text elements for instructions and inputs
    sf::Text instructionText("Enter Width (X) and Height (Y), then press Enter:", font, 24);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(10.f, 10.f);

    sf::Text xInputText("Width: ", font, 24);
    sf::Text yInputText("Height: ", font, 24);
    xInputText.setFillColor(sf::Color::White);
    yInputText.setFillColor(sf::Color::White);
    xInputText.setPosition(10.f, 80.f); // Set positions to avoid overlap and maintain layout
    yInputText.setPosition(10.f, 130.f);

    // Variables to hold user input as strings
    std::string xInput = "", yInput = "";
    bool enterPressed = false, focusOnX = true; // Control flags for input focus and completion

    // Main event and rendering loop
    while (this->_data->window.isOpen()) {
        sf::Event event;
        while (this->_data->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) this->_data->window.close();

            // Handle text input from the user
            if (!enterPressed && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Backspace logic
                    if (focusOnX && !xInput.empty()) xInput.pop_back();
                    else if (!focusOnX && !yInput.empty()) yInput.pop_back();
                } else if (event.text.unicode >= '0' && event.text.unicode <= '9') { // Numeric input
                    if (focusOnX) xInput += static_cast<char>(event.text.unicode);
                    else yInput += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == '\r') { // Enter key logic to switch focus or complete input
                    if (focusOnX) {
                        focusOnX = false; // Switch focus to height input
                        activeIndicator.setFillColor(sf::Color(250, 100, 100, 100)); // Change indicator color
                        activeIndicator.setPosition(10.f, 120.f); // Move indicator position to height input
                    } else enterPressed = true; // Completion flag set when height input is done
                }
            }
        }

        // Clear window and draw UI elements
        this->_data->window.clear();
        this->_data->window.draw(background);
        this->_data->window.draw(activeIndicator);
        // Update and draw the text elements with the current inputs
        instructionText.setString("Enter Width (X) and Height (Y), then press Enter:");
        xInputText.setString("Width: " + xInput);
        yInputText.setString("Height: " + yInput);
        this->_data->window.draw(instructionText);
        this->_data->window.draw(xInputText);
        this->_data->window.draw(yInputText);
        this->_data->window.display();

        // After inputs are completed and validated, convert them to integers and return the Position
        if (enterPressed) {
            try {
                int width = std::stoi(xInput.empty() ? "0" : xInput); // Convert width to integer
                int height = std::stoi(yInput.empty() ? "0" : yInput); // Convert height to integer
                // Validation for positive dimensions
                if (width > 0 && height > 0 && width <=50 && height<=30) {
                    return {width, height};
                } else {
                    // Reset inputs for retry if validation fails
                    instructionText.setString("Invalid input. Please enter positive numbers.");
                    enterPressed = false;
                    focusOnX = true;
                    xInput = "";
                    yInput = "";
                    activeIndicator.setPosition(10.f, 70.f);
                    activeIndicator.setFillColor(sf::Color(100, 100, 250, 100));
                }
            } catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return {-1, -1};
            }
        }
    }

    return {-1, -1}; // Return an error Position if the window is closed before completion

}



