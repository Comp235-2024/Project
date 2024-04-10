/**
* @file MapCreator.h
* @author Ricardo Raji Chahine 40234410
* @brief This class is called from the main menu and allows the user to create a map by placing objects on a grid and then either save or clear that map.
* @brief The user can place walls, doors, levers, chests, characterList, and npcs on the map.
* @brief The maps are saved as .json files in the Saved Maps directory.
*/

#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "CONFIG.h"
#include "GameLooptyLoop.h"
#include "MapObserver.h"
#include "Player.h"
#include "State.h"
#include "Movable.h"
#include "TreasureChest.h"
#include "GameLooptyLoop.h"
#include "NonPlayerCharacter.h"
#include "../../Maps/include/Lever.h"

#include <cmath>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class MapLoader : public State {
public:


    MapLoader(MainDataRef& data);

   /**
    * @brief Initializes the map creator by asking the user for the map size&name then, load all the Textures.
    */
   void Init() override;

   /**
    * @brief Handles the inputs (clicks) of the user on the window and updates the game logic.
    * @brief Either select an item from the sidebar
    * @brief Or place an item on the map
    * @brief Or clear the map
    * @brief Or save the map
    */
   void HandleInput() override;

   void Update(float deltaTime) override;

   /**
    * @brief Clear the window and then Draw all the components.
    * @param deltaTime
    */
   void Draw(float deltaTime) override;


   /**
    * @brief Struct to designate Items that are to be placed on the sidebar.
    */
   struct SidebarItem :public Movable{
       sf::Sprite sprite;
       std::string name;
       int permittedCount;
       sf::Text countText;
       sf::RectangleShape countBackground;

       SidebarItem(const std::string &name, int permittedCount);
   };

private:
   /** The number of maps in the campaign. */
   static int nbSavedMaps;

   /** The name of the map. */
   string mapName;

   /** Flag to indicate if an object is being held */
   bool isHolding = false;

   /** The map observer. */
   MapObserver mapObserver;

   /** The objects on the sidebar. */
   std::vector<SidebarItem> sidebarObjects;

   /** The selected object from the sidebar. */
   shared_ptr<Movable> selectedObject = nullptr;

   /** Items that can be placed on the map. */
   std::vector<std::string> itemNames = {"Wall", "Player", "Lever","Chest", "Door","Ogre"};

   //TODO ADD ITEM PLACEMENT LIMIT
   /** Maximum number of a specific item that can be placed on the map. */
   sf::Text itemPermittedCount;

   /** The sidebar shape/space. */
   sf::RectangleShape sidebar;

   /** Background of each item in the sidebar. */
   std::vector<sf::RectangleShape> itemContainers;

   /** The sprites for the items to be placed on the sidebar. */
   std::vector<sf::Sprite> sidebarObjectsSprites;

   /** The map shape/space. */
   sf::RectangleShape mapArea; // The map area

   /** The container for the buttons. */
   sf::RectangleShape buttonContainer;

   /** The clear button. */
   sf::RectangleShape clearButton;

   /** The save button. */
   sf::RectangleShape saveButton;

   /** The text for the clear button. */
   sf::Text clearButtonText;

   /** The text for the save button. */
   sf::Text saveButtonText;

   MainDataRef _data; /**< The main data reference. */

   shared_ptr<Map> _currentMap; /**< The current map. */
   RenderTexture _mapTexture; /**< The texture for rendering the map. */
   RenderTexture _characterView; /**< The texture for rendering the character view. */
   Sprite _bg; /**< The background sprite. */
   Vector2<unsigned int> _windowSize; /**< The window size. */

   struct Buttons {
       RectangleShape menu; /**< The menu button. */
   };

   shared_ptr<Buttons> buttons = make_shared<Buttons>(); /**< The buttons on the game screen. */

   /**
    * @brief Calculates the sizes of the textures based on the window size.
    *
    * This function calculates the sizes of the map texture, character view texture, and console view texture
    * based on the window size.
    */
   void calculateTextureSizes(int x, int y);

   /**
    * @brief Loads the textures for the map creator interface.
    */
   void loadTextures();

   /**
    * @brief Saves the edited map to a file in the Saved Maps directory as a .json file.
    */
   void saveMapToFile();

   /**
    * @brief Initializes the sidebar by specifying size and textures.
    */
   void initSideBar();

   /**
    * @brief Draws the sidebar.
    */
   void drawSideBar();

   /**
    * @brief Asks the use to enter the name and size of the map in order to resize the window and create said map.
    */
   Position askForSize();

   /**
    * @brief Initializes the buttons on the screen by specifying their sizes and their textures.
    */
   void initButtons();

   /**
    * @brief Draws the buttons on the screen.
    */
   void drawButtons();

   /**
    * @brief Assigns the current map a new default one and, detaches the observer from the old map and attaches it to the new one.
    */
   void clearMap();

   /**
    * @brief Based a click on the passed mouse position, selects an object from the sidebar.
    * @param mousePos
    */
   void selectObjectFromSidebar(const Vector2f &mousePos);

   /**
    * @brief Places an object on the map based on the passed mouse position, using the method in Map.h.
    * @param mousePos
    */
   void placeObjectOnMap(const Vector2f &mousePos);

   /**
    * @brief Checks where the user clicked on the screen eg. sidebar, map, buttons and calls the appropriate function.
    * @param mousePos Position of the click
    */
   void processClickActions(const Vector2f &mousePos);

   /**
    * @brief closes the window when the user clicks the close button.
    */
   void handleCloseEvent();

   /**
    * @brief Checks whether the event on the window was a click.
    * @param event
    */
   void handleMouseButtonPressedEvent(const Event &event);

};
#endif MAPLOADER_H
