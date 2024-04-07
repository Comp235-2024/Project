/**
 * @file GameScreen.cpp
 * @author Tymofiy Kovalenko
 * @date 22-Mar-2024
 * @brief
 */

/**
    How GameState Works

    The `GameState` enum class represents different states that the game can be in at any given time, such as `Idle`, `Moving`, `Attacking`, `Interacting`, etc.
     This allows for a clear and organized way to manage what the player and NPCs can do based on the current state of the game.
     By checking the current game state, the game knows whether to accept input for movement, initiate an attack, interact with objects, or perform other actions.

    How TurnManager Works

    The `TurnManager` class manages the turn order and interactions during the turn-based part of the game. It keeps track of all characters
     (both player and NPCs) in a vector and maintains the index of the current character whose turn it is. With each turn, it updates the
     index and notifies the game that the turn has changed. The `TurnManager` also allows adding and removing characters from the turn order,
     checking who the current player is, and drawing an indicator on the screen to show whose turn it is.

    Step by Step Example

    1. Initialization: At the start of the game or level, all player and NPC characters are added to the `TurnManager` with `addCharacter()`.
     The player character is marked as such.

    2. Starting the Turn Cycle: The game enters its main loop, and the `TurnManager` indicates it's the player's turn by checking `isPlayerTurn()`.
     A message or visual indicator is displayed using `drawWhoseTurn()`.

    3. Player's Turn:
        - The game checks the current `GameState` to determine allowable actions (e.g., moving or attacking).
        - The player performs an action, such as moving to a new tile or attacking an NPC. The game updates the state accordingly
        (e.g., `GameState::Moving` or `GameState::Attacking`).
        - Once the player's action is complete, the game updates the `GameState` back to `Idle` or another appropriate state.

    4. Advancing Turns: After the player's turn, `nextTurn()` is called to advance to the next character in the turn order.
     The `TurnManager` updates its index and checks if the next character is an NPC.

    5. NPC's Turn:
        - If it's an NPC's turn, as determined by `isNPCTurn()`, the game can automatically process the NPC's actions based on predefined AI or scripts.
        - Like the player, the NPC performs actions based on the current `GameState`.
        - Once the NPC's actions are complete, the game proceeds to the next turn.

    6. Cycle Continues: Steps 3-5 repeat until the end of the game or level. Characters can be added or removed from the turn order as needed throughout the game.

    7. End of Cycle: If the game or level ends, or a special condition is met (e.g., all enemies defeated),
     the `TurnManager` can be reset or cleared for the next game or level with `resetTurns()` or `clear()`.

    This process ensures a structured and fair turn-based system where each character gets to act in an ordered manner, allowing for strategic gameplay decisions.
 */

#include "GameScreen.h"
#include <format>

GameScreen::GameScreen(MainDataRef &data) : _data(data) {}

void GameScreen::Init() {
    ChangeState(GameState::StartScreen);

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

//            _turnManager->nextTurn();
        }

        if (_turnManager->isNPCTurn()) {
            // Draw is called in order to finish drawing the action of the player before the NPC's turn
            this->Draw(deltaTime);
            HandleNpcActions();
            _turnManager->nextTurn();
        }
    }

    switch (_gameState) {
        case GameState::StartScreen:
            break;
        case GameState::Idle:
            break;
        case GameState::Moving:
            onMoveOrAttack();
            break;
        case GameState::Attacking:
            onMoveOrAttack();
            break;
        case GameState::Interacting:
            break;
        case GameState::RollingDice:
            _diceModifier = _data->dice.roll(_diceType);
            this->notify("Dice rolled: " + to_string(_diceModifier), "Character");
            ChangeState(GameState::Idle);
            break;
        case GameState::Inventory:

            ChangeState(GameState::Idle);
            break;
        case GameState::Stats:

            ChangeState(GameState::Idle);
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

    if (_gameState == GameState::Moving || _gameState == GameState::Attacking) {
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
        _turnManager->drawWhoseTurn(_data, deltaTime);
    }

    if (_clock.getElapsedTime() > milliseconds(20) && _gameState == GameState::StartScreen) {
        handleStart();
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

        if (_turnManager->isPlayerTurn()){

            if (_data->inputs.IsButtonClicked(buttons->move, Mouse::Left, _data->window, _sideBarPosition)) {
                ChangeState(GameState::Moving);
            } else if (_data->inputs.IsButtonClicked(buttons->attack, Mouse::Left, _data->window, _sideBarPosition)) {
                ChangeState(GameState::Attacking);
            } else if (_data->inputs.IsButtonClicked(buttons->rollDice, Mouse::Left, _data->window, _sideBarPosition)) {
                ChangeState(GameState::RollingDice);
            } else if (_data->inputs.IsButtonClicked(buttons->inventory, Mouse::Left, _data->window, _sideBarPosition)) {
                ChangeState(GameState::Inventory);
            } else if (_data->inputs.IsButtonClicked(buttons->stats, Mouse::Left, _data->window, _sideBarPosition)) {
                ChangeState(GameState::Stats);
            }
        }

        if (_data->inputs.IsButtonClicked(buttons->exit, Mouse::Left, _data->window, _sideBarPosition)) {
            ChangeState(GameState::Exiting);
        } else if (_data->inputs.IsButtonClicked(buttons->start, Mouse::Left, _data->window)) {
            this->notify("Game started", "System");
            ChangeState(GameState::Idle);
            _enableFlags->turn_manager = true;
            _enableFlags->draw_whose_turn = true;
        }
    }
}
void GameScreen::handleMouseButtonMap() {
    if (Mouse::isButtonPressed(Mouse::Left) && (_gameState == GameState::Moving || _gameState == GameState::Attacking)) {
        Vector2i mousePos = Mouse::getPosition(_data->window);
        Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);
        Vector2i gridPos = Vector2i{static_cast<int>(worldPos.x / _mapObserver.SIZE_MULT), static_cast<int>(worldPos.y / _mapObserver.SIZE_MULT)};
        if (_gameState == GameState::Moving) {
            vector<Position> path = _currentMap->findPath(_player->position, gridPos);
            if (path.size() < _diceModifier + 2 && path.size() > 0) {
                if (_currentMap->move(_player->position, gridPos)) {
                    _player->position = gridPos;
                    notify("Player moved to " + to_string(gridPos.x) + ", " + to_string(gridPos.y), "Character");
                    _moveEnabled = false;
                    onMoveOrAttack();
                    ChangeState(GameState::Idle);
                }
            }
        } else if (_gameState == GameState::Attacking) {
            shared_ptr<NonPlayerCharacter> target = dynamic_pointer_cast<NonPlayerCharacter>(_currentMap->getGrid()[gridPos.y][gridPos.x]);
            if (target != nullptr) {
                notify("Player attacked target", "Character");
                _attackEnabled = false;
                notify("Enemy died due to an unbelievably strong blow", "Character");
                _currentMap->remove(gridPos);
                _turnManager->removePlayer(target);
                ChangeState(GameState::Idle);
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
            if (_currentMap->move(_player->position, newPosition)) {
                _player->position = newPosition;
                notify("Player moved", "Character");
                onMoveOrAttack();
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
                this->_npcs.back()->position = Vector2i{x, y};
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

    bool activate_buttons;
    if (_turnManager->isPlayerTurn()) {
        activate_buttons = true;
    } else {
        activate_buttons = false;
    }

    generateButton(buttons->move, buttons->moveText, "Move", 0, activate_buttons);
    _sideBarTexture.draw(buttons->move);
    _sideBarTexture.draw(buttons->moveText);

    generateButton(buttons->attack, buttons->attackText, "Attack", 1, activate_buttons);
    _sideBarTexture.draw(buttons->attack);
    _sideBarTexture.draw(buttons->attackText);

    generateButton(buttons->rollDice, buttons->rollDiceText, format("Roll {}", _diceType), 2, activate_buttons);
    _sideBarTexture.draw(buttons->rollDice);
    _sideBarTexture.draw(buttons->rollDiceText);

    generateButton(buttons->inventory, buttons->inventoryText, "Inventory", 3, activate_buttons);
    _sideBarTexture.draw(buttons->inventory);
    _sideBarTexture.draw(buttons->inventoryText);

    generateButton(buttons->stats, buttons->statsText, "Stats", 4, true);
    _sideBarTexture.draw(buttons->stats);
    _sideBarTexture.draw(buttons->statsText);

    generateButton(buttons->exit, buttons->exitText, "Exit", 5, true);
    _sideBarTexture.draw(buttons->exit);
    _sideBarTexture.draw(buttons->exitText);



    _sideBarTexture.display();
}

void GameScreen::generateButton(RectangleShape &button, Text &buttonText, const string &name, int buttonPos, bool active) {
    Font &font = _data->assets.GetFont("My Font");
    Vector2f position = Vector2f(_sideBarTexture.getSize().x / 2.0f, _sideBarTexture.getSize().y / 12.0f * (buttonPos + 1));

    //Changed the size of the button to be a third of the window width and a tenth of the window height Meaning making them less hard coded
    Vector2f size = Vector2f(_sideBarTexture.getSize().x * 0.9f, _sideBarTexture.getSize().y / 20.0f);
    button.setSize(size);
    button.setOrigin(size.x / 2.0f, size.y / 2.0f);
    button.setPosition(position);
    if (active) {
        button.setFillColor(buttonColorFill);
    } else {
        button.setFillColor(buttonInactiveColor);
    }

    buttonText.setString(name);
    buttonText.setFont(font);

    //Made a specific size for titles
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(buttonColorText);

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

void GameScreen::HandleNpcActions() {
    // NOTE each npc will be handled here depending on the lever of initiative
    // This method will be called on each individual NPC's turn

    shared_ptr<NonPlayerCharacter> npc = dynamic_pointer_cast<NonPlayerCharacter>(_turnManager->getCurrentPlayer());
    // move the npc to a random cell 2 cells away

    //random pos
    Vector2i newPos = Vector2i{rand() % 3 - 1 + npc->position.x, rand() % 3 - 1 + npc->position.y};
    this->notify("NPC moving to " + to_string(newPos.x) + ", " + to_string(newPos.y), "Character");
    if (_currentMap->move(npc->position, newPos)) {
        npc->position = newPos;
        notify("NPC moved to " + to_string(newPos.x) + ", " + to_string(newPos.y), "Character");
    }



    // Handle NPC actions here
    // For example, move the NPC character
    // or attack the player
    // or open a chest
    // or interact with a door
    // or any other action the NPC can take
    sleep(seconds(1));
}


void GameScreen::ChangeState(GameState newState) {
    // If the current game state is Moving, Attacking, Interacting, or Inventory and the new state is Idle,
    // advance the turn to the NPC's.
    if ((_gameState == GameState::Moving || _gameState == GameState::Attacking ||
        _gameState == GameState::Interacting || _gameState == GameState::Inventory) && newState == GameState::Idle) {
        _turnManager->nextTurn();
    }

    _gameState = newState;

    switch (_gameState) {
        case GameState::StartScreen:
            this->notify("Game state changed to StartScreen", "System");
            break;
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
        case GameState::Stats:
            this->notify("Game state changed to Stats", "System");
            break;
        case GameState::Exiting:
            this->notify("Game state changed to Exiting", "System");
            break;
    }
}
void GameScreen::handleStart() {

    drawStartScreen();

}
void GameScreen::drawStartScreen() {
    RectangleShape startScreen(Vector2f(_data->window.getSize().x, _data->window.getSize().y));
    startScreen.setFillColor(Color(72, 59, 58));
    startScreen.setOutlineThickness(2);
    startScreen.setOutlineColor(Color::Black);
    sf::Vector2u windowSize = _data->window.getSize();
    startScreen.setPosition((windowSize.x - startScreen.getSize().x) / 2.f, (windowSize.y - startScreen.getSize().y) / 2.f);


    buttons->startText.setFont(_data->assets.GetFont("My Font"));
    buttons->startText.setString("Start Game");
    buttons->startText.setCharacterSize(24);
    buttons->startText.setFillColor(Color(50, 50, 50));

    buttons->start.setFillColor(Color(210, 180, 140));


    Vector2f basePos{windowSize.x / 2.0f, windowSize.y * 0.2f};
    Vector2f startPos{basePos.x, basePos.y * 2};
    sf::FloatRect textRect = buttons->startText.getLocalBounds();
    buttons->startText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttons->startText.setPosition(startPos);

    buttons->start.setSize(Vector2f(textRect.getSize().x + 20, textRect.getSize().y + 20));
    buttons->start.setOrigin(buttons->start.getSize().x / 2.0f, buttons->start.getSize().y / 2.0f);
    buttons->start.setPosition(startPos);

    Text campaignInfoText;
    Vector2f campaignInfoPos{basePos.x, basePos.y * 3};
    campaignInfoText.setFont(_data->assets.GetFont("My Font"));
    campaignInfoText.setString("Map number " + to_string(_mapIndex));
    campaignInfoText.setFillColor(Color(50, 50, 50));
    campaignInfoText.setCharacterSize(24);
    sf::FloatRect campaignInfoRect = campaignInfoText.getLocalBounds();
    campaignInfoText.setOrigin(campaignInfoRect.left + campaignInfoRect.width / 2.0f, campaignInfoRect.top + campaignInfoRect.height / 2.0f);
    campaignInfoText.setPosition(campaignInfoPos);

    RectangleShape campaignInfoBox(Vector2f(campaignInfoRect.width + 20, campaignInfoRect.height + 20));
    campaignInfoBox.setFillColor(Color(210, 180, 140));
    campaignInfoBox.setOrigin(campaignInfoBox.getSize().x / 2.0f, campaignInfoBox.getSize().y / 2.0f);
    campaignInfoBox.setPosition(campaignInfoPos);




    _data->window.draw(startScreen);
    _data->window.draw(buttons->start);
    _data->window.draw(buttons->startText);
    _data->window.draw(campaignInfoBox);
    _data->window.draw(campaignInfoText);
}
