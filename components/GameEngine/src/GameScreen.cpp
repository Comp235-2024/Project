/**
 * @file GameScreen.cpp
 * @author Tymofiy Kovalenko
 * @date 22-Mar-2024
 * @brief
 */

#include "GameScreen.h"
#include <format>

GameScreen::GameScreen(MainDataRef &data) : _data(data) {}

void GameScreen::Init() {
    if (_mapIndex != 0) {
        this->_mapObserver.detach(this->_data->log);
    }
    this->_data->assets.LoadTexture("Game Background", GAME_BG_IMAGE_PATH);
    this->_data->assets.LoadFont("Font", FONT_PATH);
    //    _bg.setTexture(this->_data->assets.GetTexture("Game Background"));
    _bg.setFillColor(Color(72, 59, 58));
    _bg.setTextureRect(IntRect(0, 0, this->_data->window.getSize().x, this->_data->window.getSize().y));

    if (this->_data->campaign == nullptr) {
        this->_data->campaign = make_unique<Campaign>(_campaign);
        this->_data->campaign->attach(this->_data->log);
    }

    calculateTextureSizes();
    _currentMap = this->_data->campaign->getMap(_mapIndex);
    this->_mapObserver = MapObserver(_currentMap, &_mapTexture, _data);
    this->_mapObserver.attach(this->_data->log);

    Vector2i start = positionToVector2i(_currentMap->getStartCell());
    if (_mapIndex == 0) {
        _campaign.mike = Character(5, "knight");
    }
    _currentMap->place(_campaign.mike, start);
    _campaign.mike.position = start;
    _player = make_shared<Character>(_campaign.mike);

    // Turn manager portion
    _turnManager = make_shared<TurnManager>();
    _turnManager->addCharacter(_player, true);
    if (_data->log->enabledModules.system) {
        _turnManager->attach(_data->log);
    }
    findNPCs();


    generateMapTexture();

    _diceModifier = 3;// TODO needs to be dynamic and changed with each dice roll
    _mapIndex++;

    // TODO add all entieties to the TurnManager




}


void GameScreen::Update(float deltaTime) {

    if (_enableFlags->turn_manager) {
        if (_turnManager->isPlayerTurn()) {
            HandlePlayerActions();
            _turnManager->nextTurn();
        }

        if (_turnManager->isNPCTurn()) {
            HandleNpcActions();
            _turnManager->nextTurn();
        }
    }

    switch (_gameState) {
        case GameState::Idle:
            break;
        case GameState::Moving:
            onMoveOrAttack();
            _moveEnabled = true;
            _attackEnabled = false;
            break;
        case GameState::Attacking:
            onMoveOrAttack();
            _attackEnabled = true;
            _moveEnabled = false;
            break;
        case GameState::Interacting:
            break;
        case GameState::RollingDice:
            _diceModifier = _data->dice.roll(_diceType);
            this->notify("Dice rolled: " + to_string(_diceModifier), "Character");
            break;
        case GameState::Inventory:
            break;
        case GameState::Exiting:
            this->notify("Exiting Game", "System");
            _data->stateMachine.RemoveState();
            break;
    }


    // implement
}
void GameScreen::onMoveOrAttack() {
    scanForNearbyObjects();
}


void GameScreen::Draw(float deltaTime) {
    generateMapTexture();
    generateSideBarTexture();
    generateConsoleTexture();
    _data->window.clear();
    _data->window.draw(_bg);

    if (_moveEnabled || _attackEnabled) {
        _mapObserver.drawCircleAroundPos(_player->position, _diceModifier, Color::White, &_mapTexture);
    }

    Texture texture = _mapTexture.getTexture();
    Sprite mapSprite(texture);
    _data->window.draw(mapSprite);

    Texture sideBar = _sideBarTexture.getTexture();
    Sprite sideBarSprite(sideBar);
    sideBarSprite.setPosition(_sideBarPosition);
    _data->window.draw(sideBarSprite);

    Texture console = _consoleTexture.getTexture();
    Sprite consoleSprite(console);
    consoleSprite.setPosition(_consolePosition);
    _data->window.draw(consoleSprite);

    if (_enableFlags->draw_whose_turn) {
        _turnManager->drawWhoseTurn(_data);
    }


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
        handleKeyboardArrows();

        handleMouseButtonMap();

        if (_data->inputs.IsButtonClicked(buttons->move, Mouse::Left, _data->window, _sideBarPosition)) {
            ChangeState(GameState::Moving);
        } else if (_data->inputs.IsButtonClicked(buttons->attack, Mouse::Left, _data->window, _sideBarPosition)) {
            ChangeState(GameState::Attacking);
        } else if (_data->inputs.IsButtonClicked(buttons->rollDice, Mouse::Left, _data->window, _sideBarPosition)) {
            ChangeState(GameState::RollingDice);
        } else if (_data->inputs.IsButtonClicked(buttons->exit, Mouse::Left, _data->window, _sideBarPosition)) {
            ChangeState(GameState::Exiting);
        }
    }
}
void GameScreen::handleMouseButtonMap() {
    if (Mouse::isButtonPressed(Mouse::Left) && (_moveEnabled || _attackEnabled)) {
        Vector2i mousePos = Mouse::getPosition(_data->window);
        Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);
        Vector2i gridPos = Vector2i{static_cast<int>(worldPos.x / _mapObserver.SIZE_MULT), static_cast<int>(worldPos.y / _mapObserver.SIZE_MULT)};
        if (_moveEnabled) {
            vector<Position> path = _currentMap->findPath(_player->position, gridPos);
            if (path.size() < _diceModifier + 2 && path.size() > 0) {
                if (_currentMap->move(_player->position, gridPos)) {
                    _player->position = gridPos;
                    notify("Player moved to " + to_string(gridPos.x) + ", " + to_string(gridPos.y), "Character");
                    _moveEnabled = false;
                }
            }
        } else if (_attackEnabled) {
            shared_ptr<NonPlayerCharacter> target = dynamic_pointer_cast<NonPlayerCharacter>(_currentMap->getGrid()[gridPos.y][gridPos.x]);
            if (target != nullptr) {
                notify("Player attacked target", "Character");
                _attackEnabled = false;
                notify("Enemy died due to an unbelievably strong blow", "Character");
                _currentMap->remove(gridPos);
            } else {
                notify("No target found", "Character");
            }
        }
    }
}
void GameScreen::handleKeyboardArrows() {
    for (const auto& [key, direction] : movementBindings) {
        if (Keyboard::isKeyPressed(key)) {
            Vector2i newPosition = _player->position + direction;
            onMoveOrAttack();
            if (_currentMap->move(_player->position, newPosition)) {
                _player->position = newPosition;
                notify("Player moved", "Character");
                break;
            }
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

    int consoleWidth = _windowSize.x;
    int consoleHeight = _windowSize.y * SIDEBAR_RATIO;


    //This adjusts the size of the map texture to be 80% of the window size since sidebar takes up 20%
    _mapTexture.create(_windowSize.x * (1 - SIDEBAR_RATIO), _windowSize.y * (1 - SIDEBAR_RATIO));
    this->notify("Map texture created, size: " + to_string(_mapTexture.getSize().x) + " by " + to_string(_mapTexture.getSize().y), "System");

    _sideBarTexture.create(sidebarWidth, sidebarHeight);
    _sideBarPosition = Vector2f{static_cast<float>(_windowSize.x - sidebarWidth), 0};

    _consoleTexture.create(consoleWidth, consoleHeight);
    _consolePosition = Vector2f{0, static_cast<float>(_windowSize.y - consoleHeight)};
}

//TODO Update to use Player instead of Character and Player's location instead of searching for the character
void GameScreen::findNPCs() {
    int x = 0, y = 0;

    for (auto &row: _currentMap->getGrid()) {
        x = 0;
        for (auto &cell: row) {
            if (dynamic_cast<NonPlayerCharacter *>(cell.get())) {

                this->_npcs.push_back(dynamic_pointer_cast<NonPlayerCharacter>(cell));
                this->_turnManager->addCharacter(this->_npcs.back(), false);
                this->notify("NPC found at " + to_string(x) + ", " + to_string(y), "System");
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
            if (dynamic_cast<TreasureChest *>(_currentMap->getGrid()[newPos.y][newPos.x].get())) {
                this->notify("Chest detected nearby", "System");
            } else if (dynamic_cast<Door *>(_currentMap->getGrid()[newPos.y][newPos.x].get())) {
                this->notify("Door detected nearby", "System");
                this->Init();
            } else if (dynamic_cast<Character *>(_currentMap->getGrid()[newPos.y][newPos.x].get())) {
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

    generateButton(buttons->inventory, buttons->inventoryText, "Inventory", 3);
    _sideBarTexture.draw(buttons->inventory);
    _sideBarTexture.draw(buttons->inventoryText);

    generateButton(buttons->stats, buttons->statsText, "Stats", 4);
    _sideBarTexture.draw(buttons->stats);
    _sideBarTexture.draw(buttons->statsText);

    generateButton(buttons->exit, buttons->exitText, "Exit", 5);
    _sideBarTexture.draw(buttons->exit);
    _sideBarTexture.draw(buttons->exitText);



    _sideBarTexture.display();
}

void GameScreen::generateButton(RectangleShape &button, Text &buttonText, const string &name, int buttonPos) {
    Font &font = _data->assets.GetFont("My Font");
    Vector2f position = Vector2f(_sideBarTexture.getSize().x / 2.0f, _sideBarTexture.getSize().y / 6.0f * (buttonPos + 1));

    //Changed the size of the button to be a third of the window width and a tenth of the window height Meaning making them less hard coded
    Vector2f size = Vector2f(_sideBarTexture.getSize().x * 0.9f, _sideBarTexture.getSize().y / 20.0f);
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
void GameScreen::generateConsoleTexture() {
    _consoleTexture.clear(Color::Transparent);
    RectangleShape console(Vector2f(_consoleTexture.getSize().x, _consoleTexture.getSize().y));
    console.setFillColor(Color(72, 59, 58));
    _consoleTexture.draw(console);


    _consoleTexture.display();
}
void GameScreen::HandlePlayerActions() {
    // Handle player actions here
    // For example, move the player character
    // or attack an enemy
    // or open a chest
    // or interact with a door
    // or use an item
    // or cast a spell
    // or any other action the player can take
    this->notify("Player's turn", "System");
    sleep(seconds(2));

}
void GameScreen::HandleNpcActions() {
    // Handle NPC actions here
    // For example, move the NPC character
    // or attack the player
    // or open a chest
    // or interact with a door
    // or use an item
    // or cast a spell
    // or any other action the NPC can take
    this->notify("NPC's turn", "System");
    sleep(seconds(2));
}
void GameScreen::ChangeState(GameState newState) {
    _gameState = newState;

    switch (_gameState) {
        case GameState::Idle:
            this->notify("Game state changed to Idle", "System");
            break;
        case GameState::Moving:
            this->notify("Game state changed to Moving", "System");
            break;
        case GameState::Attacking:
            this->notify("Game state changed to Attacking", "System");
            break;
        case GameState::Interacting:
            this->notify("Game state changed to Interacting", "System");
            break;
        case GameState::RollingDice:
            this->notify("Game state changed to RollingDice", "System");
            break;
        case GameState::Inventory:
            this->notify("Game state changed to Inventory", "System");
            break;
        case GameState::Exiting:
            this->notify("Game state changed to Exiting", "System");
            break;
    }
}
