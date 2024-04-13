/**
* @file MainMenu.cpp
* @author Tymofiy Kovalenko
* @date 17-Mar-2024
* @brief
*/

#include "MapEditor.h"
#include "MapLoader.h"
#include "OptionsScreen.h"
#include "MapCreator.h"

MapEditor::MapEditor(MainDataRef data) : _data(data) {}

void MapEditor::Init() {
   this->_data->assets.LoadTexture("Menu Background", MENU_BG_IMAGE_PATH);
   this->_data->assets.LoadFont("Font", FONT_PATH);
   _bg.setTexture(this->_data->assets.GetTexture("Menu Background"));
   _bg.setTextureRect(IntRect(0,0, this->_data->window.getSize().x, this->_data->window.getSize().y));

   SetButtons();

}

void MapEditor::Update(float deltaTime) {
}

void MapEditor::Draw(float deltaTime) {
   _data->window.clear();
   _data->window.draw(_bg);

   _data->window.draw(buttons->CreateMap);
   _data->window.draw(buttons->CreateMapText);
   _data->window.draw(buttons->LoadMap);
   _data->window.draw(buttons->LoadMapText);


   Vector2i mousePos = Mouse::getPosition(_data->window);
   Vector2f worldPos = _data->window.mapPixelToCoords(mousePos);

   if (worldPos.x > 0 && worldPos.y > 0 && worldPos.y < 20 && worldPos.x < 20){
       //showMoney
       Texture tex;
       if (tex.loadFromFile(MONEY_IMAGE_PATH)){
           Sprite money(tex);
           money.setPosition(0,0);

           float scaleX = _data->window.getSize().x / money.getLocalBounds().width;
           float scaleY = _data->window.getSize().y / money.getLocalBounds().height;


           money.setScale(scaleX, scaleY);

           _data->window.draw(money);
       }
   }

   // add our names
   _data->window.display();

}

void MapEditor::HandleInput() {
   Event event{};
   while (this->_data->window.pollEvent(event)) {
       if (Event::Closed == event.type) {
           this->_data->window.close();
       }
       //Play
       if (_data->inputs.IsButtonClicked(buttons->CreateMap, Mouse::Left, _data->window)) {
           this->notify("Switching to Map Creator", "System");
           _data->stateMachine.AddState(StateRef(new MapCreator(_data)), false, _data->log);
       }

       //Map Creator
       else if (_data->inputs.IsButtonClicked(buttons->LoadMap, Mouse::Left, _data->window)) {
           this->notify("Switching to map loader", "System");
           _data->stateMachine.AddState(StateRef(new MapLoader(_data)), false, _data->log);
       }

   }
}

void MapEditor::SetButtons() {

   int nbButtons = 5;

   Font& font = _data->assets.GetFont("My Font");
   Vector2f position = Vector2f(_data->window.getSize().x/2.0f, _data->window.getSize().y/6.0f);

   //This is the spacing between the buttons
   //Changed it to be a seventh of the window height to make it less hard coded
   Vector2f spacing = Vector2f(0, _data->window.getSize().y/6.0f);

   GenerateButton(font, "Create new map ", buttons->CreateMap, buttons->CreateMapText, position);
   GenerateButton(font, "Load a Map", buttons->LoadMap, buttons->LoadMapText, position + Vector2f(0, spacing.y));

}


/**
* Very simple function to generate a button.
* Very Important: The font must be a reference to the font that is already loaded in the AssetManager.
* @param font
* @param name
* @param button
* @param buttonText
* @param position
*/
void MapEditor::GenerateButton(const Font &font, const string& name, RectangleShape &button, Text &buttonText, Vector2f position) {

   //Changed the size of the button to be a third of the window width and a tenth of the window height Meaning making them less hard coded
   Vector2f size = Vector2f(WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/10.0f);
   button.setSize(size);
   button.setOrigin(size.x / 2.0f, size.y / 2.0f);
   button.setPosition(position);
   button.setFillColor(Color(0x3f3a4daa));

   buttonText.setString(name);
   buttonText.setFont(font);

   //Made a specific size for titles
   buttonText.setCharacterSize(MENU_CHAR_TITLE_SIZE);
   buttonText.setFillColor(Color::White);

   // Adjust the text position to be centered in the new, larger button
   FloatRect textBounds = buttonText.getLocalBounds();
   buttonText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f + textBounds.top / 2.0f); // Adjust for vertical centering
   buttonText.setPosition(position);

}
