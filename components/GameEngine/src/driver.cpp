
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


int main(){
    GameLooptyLoop game(gameSize.x, gameSize.y, "DND");
    return EXIT_SUCCESS;
}
void diceLogTest() {
    LogObserver log = LogObserver("log.txt");

    Dice d;
    d.attach(&log);
    Dice::test(d);

}
