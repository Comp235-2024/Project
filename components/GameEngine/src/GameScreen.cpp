/**
 * @file GameScreen.cpp
 * @author Tymofiy Kovalenko
 * @date 22-Mar-2024
 * @brief
 */

#include "GameScreen.h"
#include <format>

GameScreen::GameScreen(MainDataRef& data) : _data(data) {}

void GameScreen::Init() {
    if(_mapIndex != 0) {
        this->_mapObserver.detach(this->_data->log);
    }
    this->_data->assets.LoadTexture("Game Background", GAME_BG_IMAGE_PATH);
    this->_data->assets.LoadFont("Font", FONT_PATH);
//    _bg.setTexture(this->_data->assets.GetTexture("Game Background"));
    _bg.setFillColor(Color(72, 59, 58));
    _bg.setTextureRect(IntRect(0,0, this->_data->window.getSize().x, this->_data->window.getSize().y));

    if (this->_data->campaign == nullptr) {

        _campaign.attach(this->_data->log);
        this->_data->campaign = make_unique<Campaign>(_campaign);
    }

    calculateTextureSizes();
    _currentMap = this->_data->campaign->getMap(_mapIndex);
    this->_mapObserver = MapObserver(_currentMap, &_mapTexture, _data);
    this->_mapObserver.attach(this->_data->log);

    Vector2i start = positionToVector2i(_currentMap->getStartCell());
    if (_mapIndex == 0) {
        _campaign.mike = Character(5, "pumpkin_dude");
    }
    _currentMap->place(_campaign.mike, start);
    _campaign.mike.position = start;
    _player = make_shared<Character>(_campaign.mike);

//    findPlayerCharacter();



    generateMapTexture();

    _diceModifier = 3; // TODO needs to be dynamic and changed with each dice roll
    _mapIndex++;


}

void GameScreen::Update(float deltaTime) {
    scanForNearbyObjects();



    // implement

}


void GameScreen::Draw(float deltaTime) {
    generateMapTexture();
    generateSideBarTexture();
    _data->window.clear();
    _data->window.draw(_bg);

    if (_moveEnabled) {
        _mapObserver.drawCircleAroundPos(_player->position, _diceModifier, Color::White, &_mapTexture);
    }

    Texture texture = _mapTexture.getTexture();
    Sprite mapSprite(texture);
    _data->window.draw(mapSprite);
    // draw menu icon
    // draw console
    Texture sideBar = _sideBarTexture.getTexture();
    Sprite sideBarSprite(sideBar);
    sideBarSprite.setPosition(_sideBarPosition);
    _data->window.draw(sideBarSprite);


    // draw character view (if any)

    // add our names
    _data->window.display();

}


void GameScreen::HandleInput() {
    Event event{};
    while (this->_data->window.pollEvent(event)) {
        if (Event::Closed == event.type) {
            this->_data->window.close();
            this->notify("Window closed", "System");
        }
        // TODO Implement the button click handling accourding to your needs
        // For transition to another state use the WelcomeScreen.cpp as an example. However,
        // don't pass a true to the AddState method, because we don't want to remove the previous state.
        // I haven't tested going back yet so exit the game and run it again if you want to go back to the previous state.
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (_currentMap->move(_player->position, Vector2i{_player->position.x, _player->position.y - 1})) {
                _player->position.y -= 1;
                this->notify("Player moved up", "Character");
            }
        } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (_currentMap->move(_player->position, Vector2i{_player->position.x, _player->position.y + 1})) {
                _player->position.y += 1;
                this->notify("Player moved down", "Character");
            }
        } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (_currentMap->move(_player->position, Vector2i{_player->position.x - 1, _player->position.y})) {
                _player->position.x -= 1;
                this->notify("Player moved left", "Character");
            }
        } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (_currentMap->move(_player->position, Vector2i{_player->position.x + 1, _player->position.y})) {
                _player->position.x += 1;
                this->notify("Player moved right", "Character");
            }
        } else if (Mouse::isButtonPressed(Mouse::Left) && _moveEnabled) {
            Vector2i mousePos = Mouse::getPosition(_data->window);
            Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);
            Vector2i gridPos = Vector2i{static_cast<int>(worldPos.x / _mapObserver.SIZE_MULT), static_cast<int>(worldPos.y / _mapObserver.SIZE_MULT)};
            vector<Position> path = _currentMap->findPath(_player->position, gridPos);
            if (path.size() < _diceModifier + 2 && path.size() > 0) {
                if (_currentMap->move(_player->position, gridPos)) {
                    _player->position = gridPos;
                    this->notify("Player moved to " + to_string(gridPos.x) + ", " + to_string(gridPos.y), "Character");
                    _moveEnabled = false;
                }
            }
        }

        if (_data->inputs.IsButtonClicked(buttons->move, Mouse::Left, _data->window, _sideBarPosition)) {
            this->notify("Move button clicked", "Character");
            _moveEnabled = true;
        } else if (_data->inputs.IsButtonClicked(buttons->attack, Mouse::Left, _data->window, _sideBarPosition)) {
            this->notify("Attack button clicked", "Character");
            _attackEnabled = true;
            _moveEnabled = true; //TODO remove this
        } else if (_data->inputs.IsButtonClicked(buttons->rollDice, Mouse::Left, _data->window, _sideBarPosition)) {
            this->notify("Roll Dice button clicked", "Character");
            _diceModifier = _data->dice.roll(_diceType);
            this->notify("Dice rolled: " + to_string(_diceModifier), "Character");


        }

    }
}

void GameScreen::generateMapTexture() {
    _mapTexture.clear(Color::Transparent);

    _mapObserver.update();

    _mapTexture.display();



}
void GameScreen::calculateTextureSizes() {
    _windowSize = _data->window.getSize();

    int sidebarWidth = _windowSize.x * SIDEBAR_RATIO;
    int sidebarHeight = _windowSize.y;

    //This adjusts the size of the map texture to be 80% of the window size since sidebar takes up 20%
    _mapTexture.create(_windowSize.x*(1-SIDEBAR_RATIO), _windowSize.y*(1-SIDEBAR_RATIO));
    this->notify("Map texture created, size: " + to_string(_mapTexture.getSize().x) + " by " + to_string(_mapTexture.getSize().y), "System");

    _sideBarTexture.create(sidebarWidth, sidebarHeight);
    _sideBarPosition = Vector2f{static_cast<float>(_windowSize.x - sidebarWidth), 0};
}

//TODO Update to use Player instead of Character and Player's location instead of searching for the character
void GameScreen::findPlayerCharacter() {
    int x = 0, y = 0;

    for (auto &row: _currentMap->getGrid()) {
        x = 0;
        for (auto &cell: row) {
            if (dynamic_cast<Character*>(cell.get())) {

               this->_player = dynamic_pointer_cast<Character>(cell);
               this->_player->position = Vector2i{x, y};
               this->notify("Player character found at " + to_string(x) + ", " + to_string(y), "System");
               return;


            }
            ++x;
        }
        ++y;
    }
}
void GameScreen::scanForNearbyObjects() {
    vector<Vector2i> directions = {Vector2i{0, 1}, Vector2i{0, -1}, Vector2i{1, 0}, Vector2i{-1, 0}};

    for (auto &dir: directions) {
        Vector2i newPos = _player->position + dir;
        if (_currentMap->isInBounds(newPos)) {
            if (dynamic_cast<TreasureChest*>(_currentMap->getGrid()[newPos.y][newPos.x].get())) {
                this->notify("Chest detected nearby", "System");
            } else if (dynamic_cast<Door*>(_currentMap->getGrid()[newPos.y][newPos.x].get())) {
                this->notify("Door detected nearby", "System");
                this->Init();
            } else if (dynamic_cast<Character*>(_currentMap->getGrid()[newPos.y][newPos.x].get())) {
                this->notify("Character detected nearby", "System");
            }
        }
    }

}
Vector2i GameScreen::positionToVector2i(Position position) {
    return Vector2i{position.x, position.y};
}
void GameScreen::generateSideBarTexture() {
    _sideBarTexture.clear(Color::Transparent);
    RectangleShape sidebar(Vector2f(_sideBarTexture.getSize().x, _sideBarTexture.getSize().y));
    sidebar.setFillColor(Color(72, 59, 58));
    _sideBarTexture.draw(sidebar);

    generateButton(buttons->move, buttons->moveText, "Move", 0);
    _sideBarTexture.draw(buttons->move);
    _sideBarTexture.draw(buttons->moveText);

    generateButton(buttons->attack, buttons->attackText, "Attack", 1);
    _sideBarTexture.draw(buttons->attack);
    _sideBarTexture.draw(buttons->attackText);

    generateButton(buttons->rollDice, buttons->rollDiceText, format("Roll {}", _diceType), 2);
    _sideBarTexture.draw(buttons->rollDice);
    _sideBarTexture.draw(buttons->rollDiceText);

    _sideBarTexture.display();
}

void GameScreen::generateButton(RectangleShape &button, Text &buttonText, const string &name, int buttonPos) {
    Font& font = _data->assets.GetFont("My Font");
    Vector2f position = Vector2f(_sideBarTexture.getSize().x/2.0f, _sideBarTexture.getSize().y/6.0f * (buttonPos+1));

    //Changed the size of the button to be a third of the window width and a tenth of the window height Meaning making them less hard coded
    Vector2f size = Vector2f(_sideBarTexture.getSize().x*0.9f, _sideBarTexture.getSize().y/20.0f);
    button.setSize(size);
    button.setOrigin(size.x / 2.0f, size.y / 2.0f);
    button.setPosition(position);
    button.setFillColor(Color(210, 180, 140));

    buttonText.setString(name);
    buttonText.setFont(font);

    //Made a specific size for titles
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(Color(50, 50, 50));

    // Adjust the text position to be centered in the new, larger button
    FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f + textBounds.top / 2.0f);// Adjust for vertical centering
    buttonText.setPosition(position);
}
