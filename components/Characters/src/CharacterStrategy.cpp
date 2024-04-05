/**
 * @file CharacterStrategy.cpp
 *
 */

#include "CharacterStrategy.h"


bool CharacterStrategy::inRange() {
    if (typeid(this) == typeid(Player)) {
        Position player_location = player->getLocation();
        Position npc_location = this->getLocation();

        int x_diff = player_location.x - npc_location.x;
        int y_diff = player_location.y - npc_location.y;

        if (x_diff < 2 && y_diff < 2) {
            return true;
        } else {
            return false;
        }
    }

    else if(typeid(this) == typeid(NonPlayerCharacter)){
        Position npc_location = npc->getLocation();
        Position player_location = this->getLocation();

        int x_diff = npc_location.x - player_location.x;
        int y_diff = npc_location.y - player_location.y;

        if (x_diff < 2 && y_diff < 2) {
            return true;
        } else {
            return false;
        }
    }
}

bool NonPlayerAggressorStrategy::move(){
    Position npc_location = this->getLocation();
    Position player_location=npc->getLocation();

    vector<Position> shortest_path=map->findPath(npc_location,player_location);

    if(map->move(npc_location,shortest_path[1])){
        this->setLocation(shortest_path[1]);
        return true;
    }
    else
        return false;
}

/*TODO: UPDATE ACCORDING TO THE OBSERVER PATTERN
TODO: IMPLEMENT INRANGE DEPENDING ON THE TYPE OF THE WEAPON EX: SWORD, BOW, ETC
TODO: ADD ANIMATION*/
bool NonPlayerAggressorStrategy::attack(){
    if(inRange()){
        player->setHealth(player->getHealth()-this->getAbilityScores(0));
        return true;
    }
    else
        return false;
}

bool NonPlayerAggressorStrategy::play(){
    if(inRange()){
        attack();
    }
    else{
        move();
    }
}


bool NonPlayerFriendlyStrategy::move(){
    Position npc_location = this->getLocation();
    Position player_location=npc->getLocation();

    vector<Position> shortest_path=map->findPath(npc_location,player_location);

    if(map->move(npc_location,shortest_path[1])){
        this->setLocation(shortest_path[1]);
        return true;
    }
    else
        return false;
}

/*
TODO: UPDATE ACCORDING TO THE OBSERVER PATTERN
TODO: IMPLEMENT INRANGE DEPENDING ON THE TYPE OF THE WEAPON EX: SWORD, BOW, ETC
TODO: ADD ANIMATION*/
bool NonPlayerFriendlyStrategy::attack(){
    if(inRange()){
        player->setHealth(player->getHealth()-this->getAbilityScores(0));
        return true;
    }
    else
        return false;
}

string NonPlayerFriendlyStrategy::getState(){
    return state;
}

void NonPlayerFriendlyStrategy::switchToAggressor(){
    state=("Aggressor");
}

bool NonPlayerFriendlyStrategy::play(){
    if(state=="Friendly"){
        move();
    }

    else if(state=="Aggressor") {
        if (inRange()) {
            attack();
        } else {
            move();
        }
    }
}

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) {
    this->player=player;
}



bool HumanPlayerStrategy::move(sf::Event event) {
    // Check if the event is a key press event.
    if (event.type != sf::Event::KeyPressed) {
        return false; // Early exit if not the correct event type.
    }

    // Determine the new position based on the key pressed.
    Position player_location = player->getLocation();
    Position new_location = player_location; // Initialize new_location with current location.

    switch (event.key.code) {
        case sf::Keyboard::Up:
            new_location.y -= 1;
            break;
        case sf::Keyboard::Down:
            new_location.y += 1;
            break;
        case sf::Keyboard::Left:
            new_location.x -= 1;
            break;
        case sf::Keyboard::Right:
            new_location.x += 1;
            break;
        default:
            return false; // Key pressed is not an arrow key, no movement occurs.
    }

    // Attempt to move the player to the new location.
    if (map->move(player_location, new_location)) {
        player->setLocation(new_location);
        return true; // Movement successful.
    } else {
        return false; // Movement failed (e.g., due to a collision).
    }
}

bool HumanPlayerStrategy::move(string direction){
    Position player_location = player->getLocation();
    Position new_location = player_location; // Initialize new_location with current location.

    if(direction=="Up"){
        new_location.y -= 1;
    }
    else if(direction=="Down"){
        new_location.y += 1;
    }
    else if(direction=="Left"){
        new_location.x -= 1;
    }
    else if(direction=="Right"){
        new_location.x += 1;
    }
    else{
        return false;
    }

    // Attempt to move the player to the new location.
    if (map->move(player_location, new_location)) {
        player->setLocation(new_location);
        return true; // Movement successful.
    } else {
        return false; // Movement failed (e.g., due to a collision).
    }
}

bool HumanPlayerStrategy::attack(NonPlayerCharacter* npc){
    if(inRange()){
            npc->setHealth(npc->getHealth()-player->getAbilityScores(0));
        return true;
    }
    else
        return false;
}

//TODO: IMPLEMENT FREE ACTION ON GUI
bool HumanPlayerStrategy::freeAction(int choice){
    switch (choice){
            case 1:
                cout<<"Content of Backpack: "<<endl;
                if(player->getBackpack().isEmpty()){
                    player->getBackpack().printItems();

                    return false;
                }

                player->getWornItems().printItems();

                cout<<"To wear an Item, enter the index of the item; else press 0: "<<endl;
                int index_choice1;
                cin>>index_choice1;

                while(index_choice1<0 || index_choice1>player->getBackpack().getSize()){
                    cout<<"Invalid Index, please enter a valid index: "<<endl;
                    cin>>index_choice1;
                }

                if(index_choice1!=0){
                    player->getWornItems().addItem(player->getBackpack().getBackpackStorage()[index_choice1]);
                    player->getBackpack().removeItem(player->getBackpack().getBackpackStorage()[index_choice1]);
                }

                break;

            case 2:
                cout<<"Content of Worn Items: "<<endl;
                if(player->getWornItems().isEmpty()){
                    player->getWornItems().printItems();

                    return false;
                }

                player->getWornItems().printItems();

                cout<<"To unwear an Item, enter the index of the item; else press 0: ";

                int index_choice2;
                cin>>index_choice2;

                while(index_choice2<0 || index_choice2>player->getWornItems().getSize()){
                    cout<<"Invalid Index, please enter a valid index: ";
                    cin>>index_choice2;
                }

                if(index_choice2!=0){
                    player->getBackpack().addItem(player->getWornItems().getItem(index_choice2));
                    player->getWornItems().removeItem(player->getWornItems().getItem(index_choice2));
                }

                break;

            default:
                cout<<"Invalid Choice"<<endl;
                break;

    }


}

void HumanPlayerStrategy::setWindowSize(const int x, const int y, float& x_win, float& y_win) {
    x_win = x * 30;
    y_win = y * 30;
}

bool HumanPlayerStrategy::play() {
    //TODO USE THE MAP THE PLAYER HAS INSTEAD OF CREATING A NEW ONE
    map=make_shared<Map>(20,20);

    bool played_attack = false;
    bool played_move = false;
    bool played_free_action = false;

    const int size_x = 20;
    const int size_y = 20;

    Position start{0, 0};
    Position end{size_x - 1, size_y - 1};

    map->setStartCell(start);
    map->setEndCell(end);

    float map_size_x{};
    float map_size_y{};
    setWindowSize(size_x, size_y, map_size_x, map_size_y);

    auto window = new RenderWindow(VideoMode(static_cast<unsigned int>(map_size_x), static_cast<unsigned int>(map_size_y * 1.2f)), "D&D Game Grid");
    window->setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("../../assets/fonts/MartianMonoNerdFontPropo-Regular.ttf")) {
            cout << "Font not loaded" << endl;
            delete window;
            return false;
    }

    RenderTexture _mapTexture;
    _mapTexture.create(window->getSize().y, window->getSize().x);

    MapObserver observer(map, &_mapTexture);

    Character mike(5);
    map->place(mike,Position{0,1});
    auto chest = TreasureChest("chest1", 20);

    map->place(chest, Position{5, 5});

    sf::Text buttons[3];
    const std::string buttonTexts[3] = {"Move", "Attack", "Free Action"};

    for (int i = 0; i < 3; ++i) {
            buttons[i].setFont(font);
            buttons[i].setString(buttonTexts[i]);
            buttons[i].setCharacterSize(24);
            buttons[i].setPosition(10, map_size_y + 30 * (i + 1));
            buttons[i].setFillColor(sf::Color::White);
    }

    bool waitingForMoveDirection = false; // Moved outside the window->isOpen() loop

    while (window->isOpen()) {
            sf::Event event{};
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                // Handle button clicks
                if (event.type == sf::Event::MouseButtonPressed) {
                    Vector2i clickPosition = Mouse::getPosition(*window);
                    Vector2f mousePos = window->mapPixelToCoords(clickPosition);

                    for (int i = 0; i < 3; ++i) {
                        if (buttons[i].getGlobalBounds().contains(mousePos)) {
                            switch (i) {
                                case 0: // Move
                                    if (!played_move) {
                                        waitingForMoveDirection = true; // Now waiting for a move direction
                                        cout << "Please press an arrow key to move.\n";
                                        played_move = true; // Mark move as done for this turn

                                    } else {
                                        cout << "You have already moved this turn.\n";
                                    }
                                    break;
                                case 1: // Attack
                                    if (!played_attack) {
                                        played_attack = true;

                                        //TODO IMPERATIVELY REMOVE THIS AND ADD NEARBY ENEMY DETECTION AND THEN ATTACK
                                        cout << "No one to attack nearby."<<endl;

                                    } else {
                                        cout << "You have already attacked this turn."<<endl;
                                    }
                                    break;
                                case 2: // Free Action
                                    if (!played_free_action) {
                                        played_free_action = true;

                                        cout<<"\n1)Access Backpack\n2)Access Worn Items"<<endl;
                                        cout<<"\nEnter your choice: "<<endl;
                                        int choice;
                                        cin>>choice;

                                        while(choice<1 || choice>2){
                                            cout<<"Invalid Choice, please enter a valid choice: ";
                                            cin>>choice;
                                        }

                                        freeAction(choice);

                                        cout << "Free action performed.\n";


                                    } else {
                                        cout << "You have already performed a free action this turn.\n";
                                    }
                                    break;
                            }
                        }
                    }
                }

                //TODO LOOK INTO WHY MAP OBJECT IS NULL
                //this waits for the user to press a key to move the player
                if (waitingForMoveDirection && event.type == sf::Event::KeyPressed) {
                    std::string moveDirection;

                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            moveDirection = "Up";
                            break;
                        case sf::Keyboard::Down:
                            moveDirection = "Down";
                            break;
                        case sf::Keyboard::Left:
                            moveDirection = "Left";
                            break;
                        case sf::Keyboard::Right:
                            moveDirection = "Right";
                            break;
                        default:
                            // If the key is not a direction, don't process further in this iteration
                            continue;
                    }

                    bool moveSuccessful = move(moveDirection); // Call the adjusted move function
                    if (moveSuccessful) {
                        cout << "Move action performed.\n";
                        played_move = true; // Mark move as done for this turn
                    } else {
                        cout << "Move failed or invalid.\n";
                    }
                    waitingForMoveDirection = false; // Reset the flag since we've handled the move
                }
            }


            window->clear();

            observer.update();

            Texture texture = _mapTexture.getTexture();
            Sprite mapSprite(texture);
            window->draw(mapSprite);

            for (const auto& button : buttons) {
                window->draw(button); // Draw buttons
            }
            window->display();
    }

    delete window;
    return true;
}
