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


    How Dice rolls work

    1. D20 dice has to be rolled by the player at the start of their turn to determine the number of tiles they can move or the range of their attack.

    2. Then the roll button is disabled and the player can move or attack based on the number rolled.

    3. When attacking, another D20 dice is rolled to determine the success of the attack. The number is kept local to the method.

    4. Everything is reset at the end of the player's turn.
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
//        _campaign.mike.textureName = this->_data->player.textureName;
        _campaign.mike = this->_data->player;

        shared_ptr<Weapon> mikeSword= make_shared<Weapon>(Weapon("Great Sword","Strength", 10));
        shared_ptr<Ring> mikeRing= make_shared<Ring>(Ring("Ring of Power","Dexterity", 5));

        Backpack backpack{"backpack1", 10};
        _campaign.mike.setBackpack(&backpack);

        _campaign.mike.getBackpack()->addItem(mikeSword);
        _campaign.mike.getBackpack()->addItem(mikeRing);

        WornItemsContainer wornItems{"wornItems1",6};
        _campaign.mike.setWornItems(&wornItems);

        shared_ptr<Helmet> mikeHelmet= make_shared<Helmet>( Helmet("Hat","Wisdom", 5));

        _campaign.mike.getWornItems().addItem(mikeHelmet);

    }
    _currentMap->place(_campaign.mike, start);
    _campaign.mike.position = start;
    _player = make_shared<Player>(_campaign.mike);

    // Turn manager portion
    if (_mapIndex == 0) {
        _turnManager = make_shared<TurnManager>();
        _turnManager->addCharacter(_player, true);
        if (_data->log->enabledModules.system) {
            _turnManager->attach(_data->log);
        }
    } else {
        _enableFlags->move = true;
        _enableFlags->attack = true;
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
    if (_npcs.size() == 0 ){
        _enableFlags->objective = true;
    }

    if (_mapIndex == 3 && _enableFlags->objective) {
        this->notify("Objective reached", "System");
        this->notify("Game Over", "System");
        this->notify("Exiting Game", "System");
        _data->stateMachine.RemoveState();
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
            if (chestFlag == 0) {
                string message="Player opened a chest at position: " + to_string(chestPositionFlag.x) + ", " + to_string(chestPositionFlag.y);
                this->notify(message, "Character");
            }

            chestFlag++;
            handleChest();

            if(chestFlag==0)
                this->notify("Player closed the chest", "Character");

            break;
        case GameState::RollingDice:
            _diceModifier = _data->dice.roll(_diceType);
            this->notify("Dice rolled: " + to_string(_diceModifier), "Character");
            ChangeState(GameState::Idle);
            break;
        case GameState::Inventory:
            //TODO Find a better way to only notify once
            if(inventoryFlag==0)
                this->notify("Inventory opened", "System");

            handleInventory();
            inventoryFlag++;

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

    drawMapStuff();

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


    if(_gameState == GameState::Inventory){
        drawInventoryScreen();
    }

    if(_gameState==GameState::Interacting){
        drawChestScreen();
    }

    // draw character view (if any)

    // add our names
    _data->window.display();
}

void GameScreen::drawMapStuff() {
    if (_gameState == GameState::Moving || _gameState == GameState::Attacking) {
        _mapObserver.drawCircleAroundPos(_player->position, _diceModifier, Color::White, &_mapTexture);
    }

    Texture texture = _mapTexture.getTexture();
    Sprite mapSprite(texture);
    _data->window.draw(mapSprite);

    drawHealthBars();
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
            } else if (_data->inputs.IsButtonClicked(buttons->endTurn, Mouse::Left, _data->window, _sideBarPosition)) {
                ChangeState(GameState::Idle);
                this->Draw(0.0f); // to reset the circle drawn if attack or move did not happen
                _enableFlags->move = true;
                _enableFlags->attack = true;
                _enableFlags->inventory = true;
                _enableFlags->roll_dice = true;
                _enableFlags->interact = true;
                _turnManager->nextTurn();
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
    if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i mousePos = Mouse::getPosition(_data->window);
        Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);
        Vector2i gridPos = Vector2i{static_cast<int>(worldPos.x / _mapObserver.SIZE_MULT), static_cast<int>(worldPos.y / _mapObserver.SIZE_MULT)};

        if (_gameState == GameState::Moving || _gameState == GameState::Attacking) {
            if (_gameState == GameState::Moving) {
                vector<Position> path = _currentMap->findPath(_player->position, gridPos);
                if (path.size() < _diceModifier + 2 && path.size() > 0) {
                    if (_currentMap->move(_player->position, gridPos)) {
                        _player->position = gridPos;
                        notify("Player moved to " + to_string(gridPos.x) + ", " + to_string(gridPos.y), "Character");
                        onMoveOrAttack();
                        ChangeState(GameState::Idle);
                        _enableFlags->move = false;
                    }
                }
            } else if (_gameState == GameState::Attacking) {
                auto target = dynamic_pointer_cast<NonPlayerCharacter>(_currentMap->getGrid()[gridPos.y][gridPos.x]);
                //TODO Update attack logic to use the player's attack value and the target's defense value
                if (target != nullptr) {
                    notify("Player attacked target", "Character");
//                    _currentMap->remove(gridPos);
//                    _turnManager->removePlayer(target);
//                    target->setHealth(target->getHitPoints()/2);
                    handleAttack(_player, target);
                    ChangeState(GameState::Idle);
                    _enableFlags->attack = false;
                    
                } else {
                    notify("No target found", "Character");
                }
            }
                
        }
        else if(_currentMap->getGrid()[gridPos.y][gridPos.x] !=nullptr && _gameState == GameState::Idle) {
            try {
                //Since there is no Button to go to Interacting state, we check if the player is near a chest and clicks on it. If so, we change the state to Interacting
                shared_ptr<TreasureChest> chest = dynamic_pointer_cast<TreasureChest>(_currentMap->getGrid()[gridPos.y][gridPos.x]);

                if (chest) {
                    if (isAdjacent(_player->position, gridPos)) {
                        ChangeState(GameState::Interacting);
                        chestPositionFlag = gridPos;
                        //TODO Add logic for interacting with Chests
                    }
                }
            }


            catch(exception& e){
                this->notify("Error: " + string(e.what()), "System");
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

            } else if (dynamic_cast<Door *>(_currentMap->getGrid()[newPos.y][newPos.x].get()) && _enableFlags->objective) {
                this->notify("Door detected nearby", "System");
                _turnManager->nextTurn();
                _turnManager->resetTurns();
                ChangeState(GameState::Idle);
                this->Draw(0.0f); // to reset the circle drawn if attack or move did not happen
                _enableFlags->move = true;
                _enableFlags->attack = true;
                _enableFlags->inventory = true;
                _enableFlags->roll_dice = true;
                _enableFlags->interact = true;
                _enableFlags->objective = false;
                this->Init();
            } else if (dynamic_cast<Character *>(_currentMap->getGrid()[newPos.y][newPos.x].get())) {
                this->notify("Character detected nearby", "System");
            }
        }
    }
}

bool GameScreen::isAdjacent(const sf::Vector2i &pos1, const sf::Vector2i &pos2){
    if(_currentMap->isInBounds(pos1) && _currentMap->isInBounds(pos2))
        return std::abs(pos1.x - pos2.x) <= 1 && std::abs(pos1.y - pos2.y) <= 1 && !(pos1 == pos2);
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

    generateButton(buttons->move, buttons->moveText, "Move", 0, activate_buttons, buttonColorFill);
    if (!_enableFlags->move || _enableFlags->roll_dice) {
        buttons->move.setFillColor(buttonInactiveColor);
    }
    _sideBarTexture.draw(buttons->move);
    _sideBarTexture.draw(buttons->moveText);

    generateButton(buttons->attack, buttons->attackText, "Attack", 1, activate_buttons, buttonColorFill);
    if (!_enableFlags->attack || _enableFlags->roll_dice) {
        buttons->attack.setFillColor(buttonInactiveColor);
    }
    _sideBarTexture.draw(buttons->attack);
    _sideBarTexture.draw(buttons->attackText);

    generateButton(buttons->rollDice, buttons->rollDiceText, format("Roll {}", _diceType), 2, activate_buttons, buttonColorFill);
    if (!_enableFlags->roll_dice) {
        buttons->rollDice.setFillColor(buttonInactiveColor);
    } else {
        buttons->rollDice.setFillColor(buttonColorFill);
    }
    _sideBarTexture.draw(buttons->rollDice);
    _sideBarTexture.draw(buttons->rollDiceText);

    generateButton(buttons->inventory, buttons->inventoryText, "Inventory", 3, activate_buttons, buttonColorFill);
    if (!_enableFlags->inventory) {
        buttons->inventory.setFillColor(buttonInactiveColor);
    }
    _sideBarTexture.draw(buttons->inventory);
    _sideBarTexture.draw(buttons->inventoryText);

    generateButton(buttons->stats, buttons->statsText, "Stats", 4, true, buttonColorFill);
    _sideBarTexture.draw(buttons->stats);
    _sideBarTexture.draw(buttons->statsText);

    generateButton(buttons->endTurn, buttons->endTurnText, "End Turn", 5, true, buttonEndTurnColor);
    _sideBarTexture.draw(buttons->endTurn);
    _sideBarTexture.draw(buttons->endTurnText);

    generateButton(buttons->exit, buttons->exitText, "Exit", 6, true, buttonExitGameColor);
    _sideBarTexture.draw(buttons->exit);
    _sideBarTexture.draw(buttons->exitText);



    _sideBarTexture.display();
}

void GameScreen::generateButton(RectangleShape &button, Text &buttonText, const string &name, int buttonPos, bool active, Color buttonColor) {
    Font &font = _data->assets.GetFont("My Font");
    Vector2f position = Vector2f(_sideBarTexture.getSize().x / 2.0f, _sideBarTexture.getSize().y / 12.0f * (buttonPos + 1));

    //Changed the size of the button to be a third of the window width and a tenth of the window height Meaning making them less hard coded
    Vector2f size = Vector2f(_sideBarTexture.getSize().x * 0.9f, _sideBarTexture.getSize().y / 20.0f);
    button.setSize(size);
    button.setOrigin(size.x / 2.0f, size.y / 2.0f);
    button.setPosition(position);
//    if (active) {
    button.setFillColor(buttonColor);
//    } else {
//        button.setFillColor(buttonInactiveColor);
//    }

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

    // show the character's stats
    Text statsText;
    Font &font = _data->assets.GetFont("My Font");
    statsText.setFont(font);
    statsText.setCharacterSize(20);
    statsText.setFillColor(Color::White);


    string stats = "Hit Points: " + to_string(_player->getHitPoints()) + "\n" +
                   "Armor Class: " + to_string(_player->getArmorClass()) + "\n" +
                   "Attack Bonus: " + to_string(_player->getAttackBonus()) + "\n" +
                   "Damage Bonus: " + to_string(_player->getDamageBonus()) + "\n";
    statsText.setString(stats);
    statsText.setPosition(10, 5);




    _consoleTexture.draw(console);
    _consoleTexture.draw(statsText);


    _consoleTexture.display();
}

void GameScreen::HandleNpcActions() {
    // NOTE each npc will be handled here depending on the lever of initiative
    // This method will be called on each individual NPC's turn

    shared_ptr<NonPlayerCharacter> npc = dynamic_pointer_cast<NonPlayerCharacter>(_turnManager->getCurrentPlayer());
    // move the npc to a random cell 2 cells away

    Vector2i playerPos = _player->position;
    Vector2i npcPos = npc->position;

    vector<Vector2i> _movementBindings = {{Vector2i{0, 1}, Vector2i{0, -1}, Vector2i{1, 0}, Vector2i{-1, 0}}};
    //find an empty cell near the player
    for (auto direction : _movementBindings) {
        Vector2i newPos = playerPos + direction;
        if (_currentMap->getGrid().at(newPos.y).at(newPos.x) == nullptr){
            playerPos = newPos;
        }
    }

    vector<Position> path = _currentMap->findPath(npcPos, playerPos);

    int range = _data->dice.roll(_diceType) / 2;
    this->notify("NPC range: " + to_string(range), "Character");

    if (path.size() <= range * 2) {
        this->notify("NPC attacking player", "Character");

        if (path.size() > 2) {
            _currentMap->move(npcPos, path.at(path.size() - 2));
            npc->position = Vector2i {path.at(path.size() - 2).x, path.at(path.size() - 2).y};
        }
        if (path.size() <= range) {
            handleAttack(npc, _player);
        }
    } else {
        this->notify("Player Not In range and is not seen", "Character");
//        _currentMap->move(npcPos, path.at(range));
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
//    if ((_gameState == GameState::Moving || _gameState == GameState::Attacking ||
//        _gameState == GameState::Interacting || _gameState == GameState::Inventory) && newState == GameState::Idle) {
//        _turnManager->nextTurn();
//    }
    if (_gameState == GameState::Attacking) {
        _enableFlags->attack = false; // This is done in case tha attack did not happen
    } else if (_gameState == GameState::Moving) {
        _enableFlags->move = false; // This is done in case tha move did not happen
    }


    switch (newState) {
        case GameState::StartScreen:
            this->notify("Game state changed to StartScreen", "System");
            break;
        case GameState::Idle:
            this->notify("Game state changed to Idle", "System");
            break;
        case GameState::Moving:
            if (!_enableFlags->move){
                this->notify("Player has already moved", "System");
                return;
            } else if (_enableFlags->roll_dice){
                this->notify("Player needs to roll the dice first", "System");
                return;
            }
            this->notify("Game state changed to Moving", "System");
            break;
        case GameState::Attacking:
            if (!_enableFlags->attack){
                this->notify("Player has already attacked", "System");
                return;
            } else if (_enableFlags->roll_dice){
                this->notify("Player needs to roll the dice first", "System");
                return;
            }
            this->notify("Game state changed to Attacking", "System");
            break;
        case GameState::Interacting:
            if (!_enableFlags->interact){
                this->notify("Player has already interacted", "System");
                return;
            }
            this->notify("Game state changed to Interacting", "System");
            break;
        case GameState::RollingDice:
            if (!_enableFlags->roll_dice) {
                this->notify("Player has already rolled the dice", "System");
                return;
            }
            _enableFlags->roll_dice = false;
            _enableFlags->move = true;
            _enableFlags->attack = true;
            this->notify("Game state changed to RollingDice", "System");

            break;
        case GameState::Inventory:
            if (!_enableFlags->inventory){
                this->notify("Player has already interacted with the inventory", "System");
                return;
            }
            this->notify("Game state changed to Inventory", "System");
            break;
        case GameState::Stats:
            this->notify("Game state changed to Stats", "System");
            break;
        case GameState::Exiting:
            this->notify("Game state changed to Exiting", "System");
            break;
    }

    _gameState = newState;
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

void GameScreen::drawInventoryScreen() {
    sf::Vector2u windowSize = _data->window.getSize();

    // Background for the inventory screen
    sf::RectangleShape inventoryScreen(sf::Vector2f(windowSize.x, windowSize.y));
    inventoryScreen.setFillColor(sf::Color(72, 59, 58));// Dark grey color
    inventoryScreen.setOutlineThickness(2);
    inventoryScreen.setOutlineColor(sf::Color::Black);

    // Calculate the positions and sizes, keeping the original proportions
    float sectionMargin = windowSize.x * 0.02f;// Margin on the sides
    float spacing = 10.0f;                     // Spacing between sections

    // Calculate widths while maintaining the original size ratio
    float wornItemsWidth = windowSize.x * 0.33f - sectionMargin - spacing / 2;
    float backpackWidth = windowSize.x * 0.67f - sectionMargin - spacing / 2;

    // Worn Items Section
    sf::RectangleShape wornItemsSection(sf::Vector2f(wornItemsWidth, windowSize.y * 0.8f));
    wornItemsSection.setFillColor(sf::Color(210, 180, 140));// Beige color
    wornItemsSection.setOutlineThickness(2);
    wornItemsSection.setOutlineColor(sf::Color::Black);
    wornItemsSection.setPosition(sectionMargin, windowSize.y * 0.1f);
    wornItemsScreenSection= wornItemsSection;

    // Worn Items Text
    sf::Text wornItemsText;
    wornItemsText.setFont(_data->assets.GetFont("My Font"));
    wornItemsText.setCharacterSize(30);               // Bigger size
    wornItemsText.setFillColor(sf::Color(30, 30, 30));// Darker color
    wornItemsText.setString("Worn Items");
    sf::FloatRect wornItemsTextRect = wornItemsText.getLocalBounds();
    wornItemsText.setOrigin(wornItemsTextRect.left + wornItemsTextRect.width / 2.0f, wornItemsTextRect.top + wornItemsTextRect.height / 2.0f);
    wornItemsText.setPosition(wornItemsSection.getPosition().x + wornItemsSection.getSize().x / 2, windowSize.y * 0.05f);

    // Backpack Section
    sf::RectangleShape backpackSection(sf::Vector2f(backpackWidth, windowSize.y * 0.8f));
    backpackSection.setFillColor(sf::Color(210, 180, 140));// Beige color
    backpackSection.setOutlineThickness(2);
    backpackSection.setOutlineColor(sf::Color::Black);
    backpackSection.setPosition(sectionMargin + wornItemsWidth + spacing, windowSize.y * 0.1f);
    backpackScreenSection=backpackSection;

    // Backpack Text
    sf::Text backpackText;
    backpackText.setFont(_data->assets.GetFont("My Font"));
    backpackText.setCharacterSize(30);               // Bigger size
    backpackText.setFillColor(sf::Color(30, 30, 30));// Darker color
    backpackText.setString("Backpack");
    sf::FloatRect backpackTextRect = backpackText.getLocalBounds();
    backpackText.setOrigin(backpackTextRect.left + backpackTextRect.width / 2.0f, backpackTextRect.top + backpackTextRect.height / 2.0f);
    backpackText.setPosition(backpackSection.getPosition().x + backpackSection.getSize().x / 2, windowSize.y * 0.05f);

    // Exit Button
    sf::RectangleShape exitButton(sf::Vector2f(100, 50));// Size of the button
    exitButton.setFillColor(sf::Color(150, 50, 50));     // Button color
    exitButton.setOutlineThickness(2);
    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setPosition(windowSize.x - 110, 10);// Positioned at the top right corner

    // Exit Button Text
    sf::Text exitButtonText;
    exitButtonText.setFont(_data->assets.GetFont("My Font"));
    exitButtonText.setCharacterSize(24);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setString("Exit");
    sf::FloatRect exitButtonTextRect = exitButtonText.getLocalBounds();
    exitButtonText.setOrigin(exitButtonTextRect.left + exitButtonTextRect.width / 2.0f, exitButtonTextRect.top + exitButtonTextRect.height / 2.0f);
    exitButtonText.setPosition(exitButton.getPosition().x + exitButton.getSize().x / 2, exitButton.getPosition().y + exitButton.getSize().y / 2);

    // Drawing the inventory screen elements
    _data->window.draw(inventoryScreen);
    _data->window.draw(wornItemsSection);
    _data->window.draw(backpackSection);
    _data->window.draw(wornItemsText);
    _data->window.draw(backpackText);
    _data->window.draw(exitButton);
    buttons->inventoryExit = exitButton;
    _data->window.draw(exitButtonText);
    buttons->inventoryExitText = exitButtonText;

    drawInventoryItems(&wornItemsSection, &backpackSection);
}

void GameScreen::drawInventoryItems(RectangleShape* wornItemsSection, RectangleShape* backpackSection) {
    Backpack* backpack = _player->getBackpack();
    WornItemsContainer& wornItems = _player->getWornItems();

    int backpackCapacity = backpack->getCapacity();
    float margin = 20.0f; // Margin for spacing

    // Adjusting sideLength to make blocks proportional and span vertically
    float availableWidth = wornItemsSection->getSize().x - 2 * margin; // Assuming margin on both sides
    float maxWidthFor3Items = wornItemsSection->getSize().x - 4 * margin; // 4 margins total for 3 items
    float sideLength = std::min(maxWidthFor3Items / 3, (wornItemsSection->getSize().y - 7 * margin) / 6);

    struct ItemSlot {
        sf::Vector2f position;
        std::string label;
    };

    int itemIndex=0;
    // Recalculate horizontal positions based on the new sideLength
    float armorX = wornItemsSection->getSize().x / 2 - sideLength / 2;
    float weaponX = armorX - sideLength - margin; // Adjusted to ensure it doesn't stick out
    float shieldRingX = armorX + sideLength + margin; // Adjusted to ensure it doesn't stick out

    std::vector<ItemSlot> itemSlots = {
            {{armorX, margin}, "Helmet"},
            {{armorX, 2 * margin + sideLength}, "Armor"},
            {{weaponX, 2 * margin + sideLength}, "Weapon"},
            {{shieldRingX, 2 * margin + sideLength}, "Shield/Ring"},
            {{armorX, 3 * margin + 2 * sideLength}, "Belt"},
            {{armorX, 4 * margin + 3 * sideLength}, "Boots"}
    };

    for (const auto& slot : itemSlots) {
        Text wornItemText;
        wornItemText.setFont(_data->assets.GetFont("My Font")); // Set the font once
        wornItemText.setCharacterSize(18); // Set character size once
        wornItemText.setFillColor(sf::Color::Black); // Set text color once

        sf::RectangleShape itemShape(sf::Vector2f(sideLength, sideLength));
        itemShape.setPosition(wornItemsSection->getPosition() + slot.position);
        itemShape.setFillColor(sf::Color(200, 200, 200)); // Placeholder color
        itemShape.setOutlineThickness(1);
        itemShape.setOutlineColor(sf::Color::Black);

        // Draw the item slot
        _data->window.draw(itemShape);

        // Checking and displaying item if it exists
        if(itemIndex < wornItems.getWornItemsContainerStorage().size()){
            shared_ptr<Item> item = wornItems.getWornItemsContainerStorage()[itemIndex];
            if (item != nullptr) {
                wornItemText.setString(item->getName());

                // Adjust font size to fit the text within its block
                adjustTextSize(wornItemText, itemShape.getSize().x - 2 * margin, itemShape.getSize().y - 2 * margin);

                // Recalculate the text bounds after font size adjustment
                sf::FloatRect textBounds = wornItemText.getLocalBounds();
                wornItemText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                wornItemText.setPosition(itemShape.getPosition().x + itemShape.getSize().x / 2.0f,
                                         itemShape.getPosition().y + itemShape.getSize().y / 2.0f - textBounds.height / 2.0f);

                _data->window.draw(wornItemText);
                wornItems.wornItemsRectangles.push_back(itemShape);
            }
        }

        // Text labels for each item slot
        sf::Text label;
        label.setFont(_data->assets.GetFont("My Font"));
        label.setString(slot.label);
        label.setCharacterSize(14);
        label.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = label.getLocalBounds();
        label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        label.setPosition(itemShape.getPosition().x + itemShape.getSize().x / 2, itemShape.getPosition().y - margin / 2);
        _data->window.draw(label);

        itemIndex++;
    }

    // Backpack Section - Make blocks square and displayed horizontally
    // Adjust the number of rows and columns based on the capacity to maintain square shape
    int backpackRows = std::ceil(std::sqrt(backpackCapacity));
    int backpackColumns = backpackRows; // Assuming a square layout for simplicity

    // Calculate the size of each item slot in the backpack
    float backpackItemSize = std::min(
            (backpackSection->getSize().x - (backpackColumns + 1) * margin) / backpackColumns,
            (backpackSection->getSize().y - (backpackRows + 1) * margin) / backpackRows);

    Text chestItemText;
    chestItemText.setFont(_data->assets.GetFont("My Font")); // Set the font once
    chestItemText.setCharacterSize(14); // Set character size once
    chestItemText.setFillColor(sf::Color::Black); // Set text color once

    // Draw backpack items
    for (int i = 0; i < backpackRows; i++) {
        for (int j = 0; j < backpackColumns; j++) {
            int index = i * backpackColumns + j;
            if (index < backpackCapacity) {
                sf::RectangleShape itemShape(sf::Vector2f(backpackItemSize,backpackItemSize)); // Square shape
                itemShape.setPosition(backpackSection->getPosition().x + j * (backpackItemSize + margin) + margin,
                                      backpackSection->getPosition().y + i * (backpackItemSize + margin) + margin); // Positioned with margins
                itemShape.setFillColor(sf::Color(150, 150, 150)); // Placeholder color
                itemShape.setOutlineThickness(2);
                itemShape.setOutlineColor(sf::Color::Black);

                if (index < backpack->getBackpackStorage().size()) {
                    shared_ptr<Item> item = backpack->getBackpackStorage()[index];
                    if (item != nullptr) {
                        // Set item name as text
                        chestItemText.setString(item->getName());

                        // Adjust font size to fit the text within its block
                        adjustTextSize(chestItemText, itemShape.getSize().x - 2 * margin, itemShape.getSize().y - 2 * margin);

                        // Recalculate the text bounds after font size adjustment
                        sf::FloatRect textBounds = chestItemText.getLocalBounds();
                        chestItemText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                        chestItemText.setPosition(itemShape.getPosition().x + itemShape.getSize().x / 2.0f,
                                                  itemShape.getPosition().y + itemShape.getSize().y / 2.0f - textBounds.height / 2.0f);
                    }
                }

                _data->window.draw(itemShape);
                if (index < backpack->getBackpackStorage().size() && backpack->getBackpackStorage()[index] != nullptr) {
                    _data->window.draw(chestItemText); // Only draw text if item exists
                    backpack->inventoryItemRectangles.push_back(itemShape);
                }
            }
        }
    }
}
void GameScreen::handleInventory() {
    if (_data->inputs.IsButtonClicked(buttons->inventoryExit, Mouse::Left, _data->window)) {
        handleInventoryExitButton();
    }if (_data->inputs.IsButtonClicked(backpackScreenSection, Mouse::Left, _data->window)) {
        processInventoryBackpackClick();
    }if (_data->inputs.IsButtonClicked(wornItemsScreenSection, Mouse::Left, _data->window)) {
        processInventoryWornItemsClick();
    }

}

void GameScreen::handleInventoryExitButton() {
    ChangeState(GameState::Idle);
    this->notify("Inventory closed", "System");

    inventoryFlag = 0;
}

void GameScreen::processInventoryBackpackClick() {
    static auto lastClickTime = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    static const std::chrono::milliseconds clickCooldown(100); // 200 milliseconds cooldown

    // Check if we are within the cooldown period after the last click
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastClickTime) < clickCooldown) {
        return;
    }

    auto backpack = _player->getBackpack();
    auto storage = backpack->getBackpackStorage();
    auto rectangles = backpack->inventoryItemRectangles;

    for (int i = 0; i < storage.size(); i++) {
        if (_data->inputs.IsButtonClicked(rectangles[i], Mouse::Left, _data->window)) {
            lastClickTime = std::chrono::high_resolution_clock::now(); // Update last click time

            auto& itemAtSlot = storage[i];
            bool selectionStateChanged = false; // Track if we changed the selection state

            // If there's an item in the slot and it's the selected item, deselect it.
            if (itemAtSlot && selectedItem == itemAtSlot) {
                selectedItem.reset();
                selectionStateChanged = true;
                this->notify("Item deselected", "System");
            }
            // If the slot has an item and it's not the selected item, select it.
            else if (itemAtSlot && selectedItem != itemAtSlot) {
                selectedItem = itemAtSlot;
                selectionStateChanged = true;
                this->notify("Item selected: " + selectedItem->getName(), "System");
            }
            // If the slot is empty and there is a selected item, move it to the slot.
            else if (!itemAtSlot && selectedItem) {
                itemAtSlot = selectedItem;
                selectedItem.reset();
                selectionStateChanged = true;
                this->notify("Item added to backpack: " + selectedItem->getName(), "System");
            }

            // If the selection state changed, exit to prevent duplicate notifications.
            if (selectionStateChanged) {
                break;
            }
        }
    }
}


void GameScreen::processInventoryWornItemsClick() {
    if (!isClickAllowed()) {
        return; // Exit if click is not allowed due to cooldown.
    }

    if (selectedItem != nullptr) {
        equipSelectedItem();
        return;
    }

    checkItemSelection();
}

bool GameScreen::isClickAllowed() {
    static auto lastClickTime = std::chrono::high_resolution_clock::now();
    const std::chrono::milliseconds clickCooldown(100); // 100 milliseconds cooldown

    auto now = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastClickTime) < clickCooldown) {
        return false;
    }
    lastClickTime = now; // Update last click time.
    return true;
}

void GameScreen::equipSelectedItem() {
    int slotIndex = getSlotIndexForItem(selectedItem->getType());

    if (slotIndex == -1) {
        this->notify("Invalid item type: " + selectedItem->getType(), "System");
        return;
    }

    auto worn = _player->getWornItems();
    auto storage = worn.getWornItemsContainerStorage();

    // Check if the slot is already taken
    if (storage[slotIndex] != nullptr) {
        this->notify("Item already equipped at this slot", "System");
        return;
    }

    // Equipping item
    storage[slotIndex] = selectedItem;
    selectedItem.reset(); // Clear the selectedItem
    this->notify("Item added to worn items: " + storage[slotIndex]->getName(), "System");
}

int GameScreen::getSlotIndexForItem(const std::string& itemType) {
    // Map each item type to a specific slot index.
    static const std::map<std::string, int> itemSlotMap = {
            {"Weapon", 2}, {"Armor", 1}, {"Helmet", 0}, {"Shield/Ring", 3},
            {"Belt", 4}, {"Boots", 5}
    };

    auto it = itemSlotMap.find(itemType);
    return it != itemSlotMap.end() ? it->second : -1;
}

void GameScreen::checkItemSelection() {
    auto worn = _player->getWornItems();
    auto storage = worn.getWornItemsContainerStorage();
    auto rectangles = worn.wornItemsRectangles;

    for (int slotIndex = 0; slotIndex < storage.size(); slotIndex++) {
        if (_data->inputs.IsButtonClicked(rectangles[slotIndex], Mouse::Left, _data->window)) {
            auto& itemAtSlot = storage[slotIndex];
            if (itemAtSlot) {
                toggleItemSelection(itemAtSlot);
                break;
            }
        }
    }
}

void GameScreen::toggleItemSelection(std::shared_ptr<Item>& itemAtSlot) {
    bool selectionStateChanged = false;

    if (selectedItem == itemAtSlot) {
        selectedItem.reset();
        selectionStateChanged = true;
        this->notify("Item deselected", "System");
    } else if (selectedItem != itemAtSlot) {
        selectedItem = itemAtSlot;
        selectionStateChanged = true;
        this->notify("Item selected: " + selectedItem->getName(), "System");
    }

    if (selectionStateChanged) {
        return;
    }
}

void GameScreen::drawChestScreen() {
    sf::Vector2u windowSize = _data->window.getSize();

    // Background for the chest screen
    sf::RectangleShape chestScreen(sf::Vector2f(windowSize.x, windowSize.y));
    chestScreen.setFillColor(sf::Color(72, 59, 58)); // Dark grey color
    chestScreen.setOutlineThickness(2);
    chestScreen.setOutlineColor(sf::Color::Black);

    float sectionMargin = windowSize.x * 0.02f; // Margin on the sides
    float spacing = 10.0f; // Spacing between sections

    // Half the width for each section (backpack and chest), minus margins and spacing
    float sectionWidth = (windowSize.x - 2 * sectionMargin - spacing) / 2;

    // Backpack Section - Left
    sf::RectangleShape backpackSection(sf::Vector2f(sectionWidth, windowSize.y * 0.8f));
    backpackSection.setFillColor(sf::Color(210, 180, 140)); // Beige color
    backpackSection.setOutlineThickness(2);
    backpackSection.setOutlineColor(sf::Color::Black);
    backpackSection.setPosition(sectionMargin, windowSize.y * 0.1f);
    backpackScreenSection = backpackSection;

    // Backpack Text
    sf::Text backpackText;
    backpackText.setFont(_data->assets.GetFont("My Font"));
    backpackText.setString("Backpack");
    backpackText.setCharacterSize(30);
    backpackText.setFillColor(sf::Color(30, 30, 30));
    sf::FloatRect backpackTextRect = backpackText.getLocalBounds();
    backpackText.setOrigin(backpackTextRect.width / 2, backpackTextRect.height / 2);
    backpackText.setPosition(backpackSection.getPosition().x + backpackSection.getSize().x / 2, windowSize.y * 0.05f);


    // Chest Section - Right
    sf::RectangleShape chestSection(sf::Vector2f(sectionWidth, windowSize.y * 0.8f));
    chestSection.setFillColor(sf::Color(210, 180, 140)); // Beige color, similar to backpack section
    chestSection.setOutlineThickness(2);
    chestSection.setOutlineColor(sf::Color::Black);
    chestSection.setPosition(sectionMargin + sectionWidth + spacing, windowSize.y * 0.1f);

    // Chest Text
    sf::Text chestText;
    chestText.setFont(_data->assets.GetFont("My Font"));
    chestText.setString("Chest");
    chestText.setCharacterSize(30);
    chestText.setFillColor(sf::Color(30, 30, 30));
    sf::FloatRect chestTextRect = chestText.getLocalBounds();
    chestText.setOrigin(chestTextRect.width / 2, chestTextRect.height / 2);
    chestText.setPosition(chestSection.getPosition().x + chestSection.getSize().x / 2, windowSize.y * 0.05f);

    // Exit Button
    sf::RectangleShape exitButton(sf::Vector2f(100, 50));// Size of the button
    exitButton.setFillColor(sf::Color(150, 50, 50));     // Button color
    exitButton.setOutlineThickness(2);
    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setPosition(windowSize.x - 110, 10);// Positioned at the top right corner

    //Exit Button text
    sf::Text exitButtonText;
    exitButtonText.setFont(_data->assets.GetFont("My Font"));
    exitButtonText.setCharacterSize(24);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setString("Exit");
    sf::FloatRect exitButtonTextRect = exitButtonText.getLocalBounds();
    exitButtonText.setOrigin(exitButtonTextRect.left + exitButtonTextRect.width / 2.0f, exitButtonTextRect.top + exitButtonTextRect.height / 2.0f);
    exitButtonText.setPosition(exitButton.getPosition().x + exitButton.getSize().x / 2, exitButton.getPosition().y + exitButton.getSize().y / 2);


    // Drawing the chest screen elements
    _data->window.draw(chestScreen);
    _data->window.draw(backpackSection);
    _data->window.draw(chestSection);
    _data->window.draw(backpackText);
    _data->window.draw(chestText);
    _data->window.draw(exitButton);
    buttons->chestExit = exitButton;
    _data->window.draw(exitButtonText);
    buttons->chestExitText = exitButtonText;

    //TODO Call drawChestItems with the position of the chest
    drawChestItems(&chestSection, &backpackSection);

}

void GameScreen::drawChestItems(sf::RectangleShape *chestItemsSection, sf::RectangleShape *backpackItemsSection) {
    Position position=chestPositionFlag;

    Backpack* backpack = _player->getBackpack();
    std::shared_ptr<TreasureChest> chest = std::dynamic_pointer_cast<TreasureChest>(_currentMap->getGrid()[position.y][position.x]); // This method needs to be implemented based on your game's design.

    int backpackCapacity = backpack->getCapacity();
    int chestCapacity = chest->getCapacity(); // Assuming Chest has a similar method to get its capacity.
    float margin = 20.0f; // Margin for spacing

    // Common setup for both sections
    float sectionWidth = chestItemsSection->getSize().x - 2 * margin; // Assuming equal width for both sections
    int rows = std::ceil(std::sqrt(std::max(backpackCapacity, chestCapacity))); // Determine row count based on the larger of backpack or chest capacity
    float itemSize = std::min((chestItemsSection->getSize().x - (rows + 1) * margin) / rows,
                              (chestItemsSection->getSize().y - (rows + 1) * margin) / rows); // Ensure squares



    // Draw backpack items
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            int index = i * rows + j;
            if (index < backpackCapacity) {
                Text backpackItemText;
                backpackItemText.setFont(_data->assets.GetFont("My Font")); // Set the font once
                backpackItemText.setCharacterSize(14); // Set character size once
                backpackItemText.setFillColor(sf::Color::Black); // Set text color once


                sf::RectangleShape itemShape(sf::Vector2f(itemSize, itemSize)); // Square shape
                itemShape.setPosition(backpackItemsSection->getPosition().x + j * (itemSize + margin) + margin,
                                      backpackItemsSection->getPosition().y + i * (itemSize + margin) + margin); // Positioned with margins
                itemShape.setFillColor(sf::Color(150, 150, 150)); // Placeholder color
                itemShape.setOutlineThickness(2);
                itemShape.setOutlineColor(sf::Color::Black);

                if (index < backpack->getBackpackStorage().size()) {
                    shared_ptr<Item> item = backpack->getBackpackStorage()[index];
                    if (item != nullptr) {
                        // Set item name as text
                        backpackItemText.setString(item->getName());

                        // Adjust font size to fit the text within its block
                        adjustTextSize(backpackItemText, itemShape.getSize().x - 2 * margin, itemShape.getSize().y - 2 * margin);

                        // Recalculate the text bounds after font size adjustment
                        sf::FloatRect textBounds = backpackItemText.getLocalBounds();
                        backpackItemText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                        backpackItemText.setPosition(itemShape.getPosition().x + itemShape.getSize().x / 2.0f,
                                                  itemShape.getPosition().y + itemShape.getSize().y / 2.0f - textBounds.height / 2.0f);
                    }
                }

                _data->window.draw(itemShape);
                if (index < backpack->getBackpackStorage().size() && backpack->getBackpackStorage()[index] != nullptr) {
                    _data->window.draw(backpackItemText); // Only draw text if item exists
                }
            }
        }
    }


    // Draw chest items
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            int index = i * rows + j;
            if (index >= chestCapacity) continue; // Skip if index exceeds chest capacity

            Text chestItemText;
            chestItemText.setFont(_data->assets.GetFont("My Font")); // Set the font once
            chestItemText.setCharacterSize(14); // Set character size once
            chestItemText.setFillColor(sf::Color::Black); // Set text color once

            // Create item shape
            sf::RectangleShape itemShape(sf::Vector2f(itemSize, itemSize));
            itemShape.setPosition(chestItemsSection->getPosition().x + j * (itemSize + margin) + margin,
                                  chestItemsSection->getPosition().y + i * (itemSize + margin) + margin);
            itemShape.setFillColor(sf::Color(150, 150, 150));
            itemShape.setOutlineThickness(2);
            itemShape.setOutlineColor(sf::Color::Black);

            // Draw item if present
            if (index < chest->getSize()) {
                shared_ptr<Item> item = chest->getTreasureChestStorage()[index];
                if (item != nullptr) {
                    // Set item name as text
                    chestItemText.setString(item->getName());

                    // Adjust font size to fit the text within its block
                    adjustTextSize(chestItemText, itemShape.getSize().x - margin, itemShape.getSize().y - margin);

                    // Center the text within its block after adjusting its size
                    sf::FloatRect textBounds = chestItemText.getLocalBounds();
                    chestItemText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    chestItemText.setPosition(itemShape.getPosition().x + itemShape.getSize().x / 2.0f,
                                              itemShape.getPosition().y + itemShape.getSize().y / 2.0f - textBounds.height / 2.0f);

                }
            }

            // Draw item shape and text
            _data->window.draw(itemShape);
            if (index < chest->getSize() && chest->getTreasureChestStorage()[index] != nullptr) {
                _data->window.draw(chestItemText); // Only draw text if item exists
                chest->chestItemRectangles.push_back(itemShape);
            }
        }
    }
}

void GameScreen::handleChest() {
    //TODO Handle item interactions in the chest screen

    handleChestExitButton();
}

void GameScreen::handleChestExitButton() {
    if(_data->inputs.IsButtonClicked(buttons->chestExit, Mouse::Left, _data->window)) {
        ChangeState(GameState::Idle);
        this->notify("Chest closed", "System");
        chestPositionFlag={-1,-1};
        chestFlag=0;
    }
}

void GameScreen::adjustTextSize(sf::Text &text, float maxWidth, float maxHeight) {
    // Ensure the method starts with a character size that's likely too big, then adjust down.
    unsigned int characterSize = text.getCharacterSize();
    sf::FloatRect bounds = text.getLocalBounds();

    // Determine an upper bound for character size that's definitely too large to fit.
    float initialScaleFactor = std::min(maxWidth / bounds.width, maxHeight / bounds.height);
    characterSize = static_cast<unsigned int>(characterSize * initialScaleFactor);
    text.setCharacterSize(characterSize);
    bounds = text.getLocalBounds();

    // Decrease character size until the text fits within maxWidth and maxHeight
    while ((bounds.width > maxWidth || bounds.height > maxHeight) && characterSize > 0) {
        --characterSize;
        text.setCharacterSize(characterSize);
        bounds = text.getLocalBounds();
    }

    // Incrementally increase character size to maximize use of available space, ensuring a margin
    // Note: This loop may be optionally skipped if you want to ensure a margin is always present
    while (characterSize < maxHeight) {
        ++characterSize;
        text.setCharacterSize(characterSize);
        bounds = text.getLocalBounds();

        if (bounds.width > maxWidth || bounds.height > maxHeight) {
            // Undo the last increase if it made the text too big
            --characterSize;
            text.setCharacterSize(characterSize);
            break; // Exit the loop as we've found the limit
        }
    }
}

void GameScreen::drawHealthBars() {

    auto createHealthBar = [this](Vector2i pos, bool isPlayer, unsigned int health) {
        Vector2f pixelPos = static_cast<Vector2f>(pos) * _mapObserver.SIZE_MULT;

        RectangleShape bar;
        if (isPlayer) {
            bar.setFillColor(Color::Green);
        } else {
            bar.setFillColor(Color::Red);
        }
        bar.setOutlineThickness(1);
        bar.setOutlineColor(Color::Black);
        bar.setSize(Vector2f{_mapObserver.SIZE_MULT * health/100, _mapObserver.SIZE_MULT * 0.1f});
        bar.setPosition(pixelPos + Vector2f{0, _mapObserver.SIZE_MULT * 0.1f});

        this->_data->window.draw(bar);
    };



    for (auto entity : _npcs){
        createHealthBar(entity->position, false, entity->getHitPoints());
    }
    createHealthBar(_player->position, true, _player->getHitPoints());
}

void GameScreen::handleAttack(shared_ptr<Player> player, shared_ptr<NonPlayerCharacter> npc) {
    int p_attack_bon = player->getAttackBonus();

    int npc_hp = npc->getHitPoints();
    int npc_armor = npc->getArmorClass();
    int p_weapon_dmg = 0;

    try {
        auto p_weapon = (player->getWornItems().getWornItemsContainerStorage().at(2));
        p_weapon_dmg = p_weapon->getEnchantmentLevel();
    } catch (...){
        this->notify("Player does not have a weapon equipped", "Character");
        this->notify("Using fists", "Character");
        p_weapon_dmg = 80;
    }

    // add dice mod
    float roll = static_cast<float>(_data->dice.roll("1d20"));
    roll = (roll - 1) / 10;

    // calculate damage with the formula (attack bonus + weapon damage - armor class) * roll where roll is a random number between 0 and 19
    int p_dmg = p_attack_bon + p_weapon_dmg - npc_armor;
    p_dmg = p_dmg * roll;
    this->notify("Player attacked NPC with " + to_string(p_dmg) + " damage", "Character");

    npc_hp -= p_dmg;
    if (npc_hp <= 0) {
        npc->setHitPoints(0);
        make_npc_into_chest(npc->position);
        player->levelUp();
        this->notify("NPC died and turned into chest", "Character");
        _turnManager->removePlayer(npc);
        auto it = find(_npcs.begin(), _npcs.end(), npc);
        if (it != _npcs.end()) {
            _npcs.erase(it);
        }

    } else {
        npc->setHitPoints(npc_hp);
        this->notify("Player attacked NPC", "Character");
        this->notify("NPC hitpoints: " + to_string(npc_hp), "Character");
    }
}

void GameScreen::handleAttack( shared_ptr<NonPlayerCharacter> npc, shared_ptr<Player> player) {
    int npc_attack_bon = npc->getAttackBonus();

    int player_hp = player->getHitPoints();
    int player_armor = player->getArmorClass();
    int npc_weapon_dmg = 20;

    try {
//        auto p_weapon = dynamic_cast<Weapon *>(player->getWornItems().getWornItemsContainerStorage().at(2));
//        npc_weapon_dmg = p_weapon->getEnchantmentLevel();
    } catch (...){
        this->notify("Player does not have a weapon equipped", "Character");
        this->notify("Using the default bow", "Character");
        npc_weapon_dmg = 30;
    }

    // add dice mod
    float roll = static_cast<float>(_data->dice.roll("1d20"));
    roll = (roll - 1) / 10;

    // calculate damage with the formula (attack bonus + weapon damage - armor class) * roll where roll is a random number between 0 and 19
    int npc_dmg = npc_attack_bon + npc_weapon_dmg - player_armor;
    npc_dmg = npc_dmg * roll;
    this->notify("Player attacked NPC with " + to_string(npc_dmg) + " damage", "Character");

    if (npc_dmg < 0) {
        npc_dmg = -npc_dmg;
    }

    player_hp -= npc_dmg;
    if (player_hp <= 0) {
        player->setHitPoints(0);
        this->notify("Player died", "Character");
        this->notify("Game over", "Character");
        ChangeState(GameState::Exiting);

    } else {
        player->setHitPoints(player_hp);
        this->notify("NPC attacked", "Character");
        this->notify("Player hitpoints: " + to_string(player_hp), "Character");
    }
}


void GameScreen::make_npc_into_chest(Vector2i vector2) {

    shared_ptr<TreasureChest> dead_npc = make_shared<TreasureChest>();
    shared_ptr<Armor> armor = make_shared<Armor>(Armor("God Armor", Armor::enchantment_types[0], 12));
    shared_ptr<Weapon> weapon = make_shared<Weapon>(Weapon("God Weapon", Weapon::enchantment_types[0], 12));

    dead_npc->addItem(armor);
    dead_npc->addItem(weapon);

    _currentMap->remove(vector2);
    _currentMap->place(dead_npc, vector2);
}
