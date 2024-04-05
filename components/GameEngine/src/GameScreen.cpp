/**
 * @file GameScreen.cpp
 * @author Tymofiy Kovalenko
 * @date 22-Mar-2024
 * @brief
 */

#include "GameScreen.h"

GameScreen::GameScreen(MainDataRef data) : _data(data) {}

void GameScreen::Init() {
    if(_mapIndex != 0) {
        this->mapObserver.detach(this->_data->log);
    }
    this->_data->assets.LoadTexture("Game Background", GAME_BG_IMAGE_PATH);
    this->_data->assets.LoadFont("Font", FONT_PATH);
    _bg.setTexture(this->_data->assets.GetTexture("Game Background"));
    _bg.setTextureRect(IntRect(0,0, this->_data->window.getSize().x, this->_data->window.getSize().y));
    if (this->_data->campaign == nullptr) {

        _campaign.attach(this->_data->log);
        this->_data->campaign = make_unique<Campaign>(_campaign);
    }

    calculateTextureSizes();
    _currentMap = this->_data->campaign->getMap(_mapIndex);
    this->mapObserver = MapObserver(_currentMap, &_mapTexture, _data);
    this->mapObserver.attach(this->_data->log);
    if(_mapIndex != 0) {
        _currentMap->place(_campaign.mike, Position{0, 0});
        _campaign.mike.textureName = "imp";
    }

    findPlayerCharacter();



    generateMapTexture();
    _mapIndex++;


}

void GameScreen::Update(float deltaTime) {
    // TODO implement nearby detection
    scanForNearbyObjects();



    // implement

}

void GameScreen::Draw(float deltaTime) {
    generateMapTexture();
    _data->window.clear();
    _data->window.draw(_bg);
    // draw map view
    Texture texture = _mapTexture.getTexture();
    Sprite mapSprite(texture);
    _data->window.draw(mapSprite);
    // draw menu icon
    // draw console
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
        }

    }
}

void GameScreen::generateMapTexture() {
    _mapTexture.clear(Color::Transparent);
    //TODO implement complex maps and their rendering

    //

//    mapObserver.updateMapOnly(&_mapTexture);
    mapObserver.update();

    _mapTexture.display();



}
void GameScreen::calculateTextureSizes() {
    _windowSize = _data->window.getSize();
    // TODO make the console and character view sizes dynamic
    _mapTexture.create(_windowSize.x, _windowSize.y);
    this->notify("Map texture created, size: " + to_string(_mapTexture.getSize().x) + " by " + to_string(_mapTexture.getSize().y), "System");
}
void GameScreen::findPlayerCharacter() {
    int x = 0, y = 0;
    for (auto &row: _currentMap->getGrid()) {
        x = 0;
        for (auto &cell: row) {
            if (dynamic_cast<Character*>(cell.get())) {
//                this->_player = cell.get();
                this->_player = dynamic_pointer_cast<Character>(cell);

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
