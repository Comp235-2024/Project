
#include "../../Functionalities/include/Dice.h"
#include "CharacterObserver.h"
#include "Item.h"
#include "Map.h"
//#include "../tests/ItemsTest.cpp"
#include "Campaign.h"
#include "MapObserver.h"
#include <iostream>
#include "Player.h"
#include "CharacterStrategy.h"
using namespace std;
using namespace sf;
#include "../include/GameLooptyLoop.h"
#include "Character.h"
#include "TankBuilder.h"
#include "NimbleBuilder.h"
#include "BullyBuilder.h"

#include "../include/CONFIG.h"
#include "SFML/Graphics.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Listener.hpp>
const Vector2f gameSize = {WINDOW_WIDTH, WINDOW_HEIGHT};


void diceLogTest();
int main(){

    //Character::testLevelUpProcess();
    //diceLogTest();
    Music music;

    if (!music.openFromFile("../../assets/audios/music1.ogg"))
    {
        std::cerr << "Error while loading background music file" << std::endl;
        return -1;
    }

    music.setVolume(100.f);
    music.setLoop(true);
    music.play();



    Character::testLevelUpProcess();
    diceLogTest();

    GameLooptyLoop game(gameSize.x, gameSize.y, "DND");

//    Player player;
//    auto* humanPlayerStrategy = new HumanPlayerStrategy(&player);
//    player.setStrategy(humanPlayerStrategy);
//
//    player.getStrategy()->play();


    return EXIT_SUCCESS;
}
void diceLogTest() {
    LogObserver log = LogObserver("log.txt");

    Dice d;
    d.attach(&log);
    Dice::test(d);

}


//void characterTestDriver() {
//    Character *character = new Character(0);
//    CharacterObserver *characterObservable = new CharacterObserver(character);
//    cout << "------ SHOWING THE ORIGINAL CREATED CHARACTER: ------" << endl;
//    character -> notify();
//    character->interactiveCharacterTest();
//}
//
//void tests() {
////    cout << "Testing Map class" << endl;
////    Map::map_test();
////
////    cout << "________________________________________________________" << endl;
////
////    cout << "Testing Dice class" << endl;
////    Dice d;
////    Dice::test(d);
//
//    cout << "________________________________________________________" << endl;
//    cout << "<<<<<< Testing Character class >>>>>>" << endl;
//    characterTestDriver();
//
//
////    cout << "________________________________________________________" << endl;
////    cout << "Testing Item class" << endl;
////    srand(static_cast<unsigned int>(time(nullptr)));
////    Item::item_test();
//}
//
//void setWindowSize(const int x, const int y, float& x_win, float& y_win) {
//    x_win = x * SIZE_MULT;
//    y_win = y * SIZE_MULT;
//}
//
//void campaignTest() {
//    std::string decision;
//    int height;
//    int width;
//    std::string input;// Temporary string to hold input
//    Campaign newCampaign;
//
//
//    while (true) {
//        std::cout << "Do you want to create a new map? (yes/no): ";
//        std::getline(std::cin, decision);
//
//        if (decision == "yes" | decision == "y") {
//            std::cout << "What is the height of the map?";
//            std::getline(std::cin, input); // Read input as a string
//            std::istringstream(input) >> height; // Convert string to integer
//            std::cout << "What is the width of the map?";
//            std::getline(std::cin, input); // Read input as a string
//            std::istringstream(input) >> width;
//            Map newMap(height,width);
//            std::cout << "Do you want to add this map to the campaign? (yes/no): ";
//            std::getline(std::cin, decision);
//            if (decision == "yes" | decision == "y") {
//                newCampaign.addMap(newMap);
//                std::string filename = "campaign_user_choice.json";
//                newCampaign.saveToJson(filename);
//                std::cout << "Campaign saved to " << filename << std::endl;
//            } else if(decision == "no" | decision == "n")
//                continue;
//
//        } else if (decision == "no" | decision == "n") {
//            std::cout << "Exiting map creation." << std::endl;
//            break;
//        } else {
//            std::cout << "Please enter 'yes' or 'no'." << std::endl;
//        }
//    }
//
//
//
//
//
//
//
//
//    sf::RenderWindow window(sf::VideoMode(800, 600), "D&D Game Grid");
//    sf::RectangleShape line(sf::Vector2f(800, 1)); // Horizontal line
//    sf::RectangleShape line_v(sf::Vector2f(1, 600)); // Vertical line
//    line.setFillColor(sf::Color::White);
//
//    Campaign myCampaign;
//    Map myMap(20, 15);
//
//    Map map1(20, 15); // Example dimensions
//    Map map2(25, 10); // Adjust sizes as needed for your test
//
//    myCampaign.addMap(map1);
//    myCampaign.addMap(map2);
//
//    std::string filename = "campaign.json";
//    myCampaign.saveToJson(filename);
//    std::cout << "Campaign saved to " << filename << std::endl;
//
//
//    // Step 3: Load Campaign from JSON
//    Campaign loadedCampaign;
//    if (loadedCampaign.loadFromJson(filename)) {
//        std::cout << "Campaign loaded from " << filename << std::endl;
//        loadedCampaign.printCampaignDetails();  // Assuming this method exists for debugging
//    } else {
//        std::cerr << "Failed to load campaign from " << filename << std::endl;
//    }
//
//    cout << "Number of maps in the campaign: " << myCampaign.getNumberOfMaps() << endl;
//    myCampaign.printCampaignDetails(); // Assuming you've implemented this method
//
//    while (window.isOpen()) {
//        sf::Event event{};
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            if (event.type == sf::Event::MouseButtonPressed) {
//                // Convert click position to grid coordinates
//                int gridX = event.mouseButton.x / 40; // Assuming cell size is 40x40 pixels
//                int gridY = event.mouseButton.y / 40;
//
//                // Left mouse button adds a wall, right mouse button removes it
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    myMap.place(Wall(), Position(gridX, gridY));
//                } else if (event.mouseButton.button == sf::Mouse::Right) {
//                    myMap.remove(Position(gridX, gridY));
//                }
//            }
//        }
//
//
//        window.clear();
//
//        // Draw grid lines
//        for (int y = 0; y < myMap.getSizeY(); y++) {
//            for (int x = 0; x < myMap.getSizeX(); x++) {
//                sf::RectangleShape cell(sf::Vector2f(40 - 1, 40 - 1)); // Cell size minus a small gap
//                cell.setPosition(x * 40, y * 40);
//                if (dynamic_cast<Wall*>(myMap.getGrid()[y][x].get())) {
//                    cell.setFillColor(sf::Color::Blue); // Wall color
//                } else {
//                    cell.setFillColor(sf::Color::White); // Empty cell color
//                }
//                window.draw(cell);
//            }
//        }
//
//        window.display();
//    }
//
//}
//
///**
// * Function to test the map observer.
// * It creates a window and a map, and allows the user to move a character around the map using the arrow keys.
// */
//void mapObserverTest() {
//
//    const int size_x = 20;
//    const int size_y = 20;
//
//    Map map(size_x, size_y);
//
//    float map_size_x{};
//    float map_size_y{};
//
//    setWindowSize(size_x, size_y, map_size_x, map_size_y);
//    float window_size_x{map_size_x};
//    float window_size_y{map_size_y * 1.2f};
//
//    auto* window = new RenderWindow(VideoMode(window_size_x, window_size_y) , "D&D Game Grid");
//    window->setFramerateLimit(60);
//
//    const float consoleWindowHeight = map_size_y * 0.2f;
//    const Vector2f consoleSize(window->getSize().x, consoleWindowHeight);
//
//    RectangleShape consoleBg(consoleSize);
//    consoleBg.setPosition(0, window->getSize().y - consoleWindowHeight);
//    consoleBg.setFillColor(Color(50, 50, 50, 200));
//
//
//    Font font;
//    if (!font.loadFromFile("../../assets/fonts/MartianMonoNerdFontPropo-Regular.ttf")) {
//        cout << "Font not loaded" << endl;
//        return;
//    }
//
//
//    Text consoleText("", font, 15);
//    consoleText.setPosition(5, map_size_y + 5);
//    consoleText.setFillColor(Color::White);
//
//    string userInput;
//
//
//    MapObserver observer(&map, window, map_size_x, map_size_y);
//
//    Character mike{5};
//
//    map.place(mike, Position{9, 9});
//
//    shared_ptr<TreasureChest> chest = make_shared<TreasureChest>("chest1", 20);
//    map.place(chest, Position{5, 5});
//
//    string focused = "map";
//    Position characterPos{9, 9};
//
//    while (window->isOpen()) {
//        Event event{};
//        while (window->pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                window->close();
//            }
//
//            if (event.type == Event::MouseButtonPressed) {
//                cout << "x: " << event.mouseButton.x << " y: " << event.mouseButton.y << endl;
//                cout << "map size x: " << map_size_x << " map size y: " << map_size_y << endl;
//                cout << "mouse pressed" << endl;
//                if (event.mouseButton.y > map_size_y && event.mouseButton.x < map_size_x) {
//                    focused = "console";
//                    cout << "console" << endl;
//                } else if (event.mouseButton.y <= map_size_y && event.mouseButton.x < map_size_x) {
//                    focused = "map";
//                    cout << "map" << endl;
//                } else {
//                    focused = "none";
//                }
//            }
//
//            if (focused == "map") {
//                if (Keyboard::isKeyPressed(Keyboard::Up)) {
//                    cout << "bup" << endl;
//                    if (map.move(characterPos, Position{characterPos.x, characterPos.y - 1})) {
//                        characterPos.y -= 1;
//                        cout << "up" << endl;
//                    }
//                } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
//                    if (map.move(characterPos, Position{characterPos.x, characterPos.y + 1})) {
//                        characterPos.y += 1;
//                    }
//                } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
//                    if (map.move(characterPos, Position{characterPos.x - 1, characterPos.y})) {
//                        characterPos.x -= 1;
//                    }
//                } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
//                    if (map.move(characterPos, Position{characterPos.x + 1, characterPos.y})) {
//                        characterPos.x += 1;
//                    }
//                }
//
//            } else if (focused == "console") {
//                if (event.type == Event::TextEntered) {
//                    if (event.text.unicode == '\b' && !userInput.empty()) {
//                        userInput.pop_back();
//                    } else if (event.text.unicode == '\r') { // enter
//                        userInput = ""; // TODO make it execute something
//
//                    } else if (event.text.unicode < 128) {
//                        userInput += static_cast<char>(event.text.unicode);
//
//                    }
//                }
//            }
//
//        }
//
//        consoleText.setString("$ " + userInput);
//        window->clear();
//        observer.updateMapOnly(window);
//        window->draw(consoleBg);
//        window->draw(consoleText);
//        window->display();
//
//        Wall wall;
//
//        for (int i = 0; i < 12; ++i) {
//            map.place(wall, Position{1, i});
//        }
//    }
//
//}
//
//
//int main() {
//
//    Map::mapBuilderTest();
//    tests();
//    campaignTest();
//    mapObserverTest();
//
//
//   return 0;
//}
