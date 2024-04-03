/**
 * @file MainMenu.cpp
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#include "MainMenu.h"
#include "GameScreen.h"

MainMenu::MainMenu(MainDataRef data) : _data(data) {}

void MainMenu::Init() {
    this->_data->assets.LoadTexture("Menu Background", MENU_BG_IMAGE_PATH);
    this->_data->assets.LoadFont("Font", FONT_PATH);
    _bg.setTexture(this->_data->assets.GetTexture("Menu Background"));
    _bg.setTextureRect(IntRect(0,0, this->_data->window.getSize().x, this->_data->window.getSize().y));

    SetButtons();

}

void MainMenu::Update(float deltaTime) {
}

void MainMenu::Draw(float deltaTime) {
    _data->window.clear();
    _data->window.draw(_bg);

    _data->window.draw(buttons->play);
    _data->window.draw(buttons->playText);
    _data->window.draw(buttons->editMap);
    _data->window.draw(buttons->editMapText);
    _data->window.draw(buttons->editCharacter);
    _data->window.draw(buttons->editCharacterText);
    _data->window.draw(buttons->load);
    _data->window.draw(buttons->loadText);
    _data->window.draw(buttons->options);
    _data->window.draw(buttons->optionsText);
    _data->window.draw(buttons->quit);
    _data->window.draw(buttons->quitText);

    // add our names
    _data->window.display();

}

void MainMenu::HandleInput() {
    Event event{};
    while (this->_data->window.pollEvent(event)) {
        if (Event::Closed == event.type) {
            this->_data->window.close();
        }
        // TODO Implement the button click handling accourding to your needs
        // For transition to another state use the WelcomeScreen.cpp as an example. However,
        // don't pass a true to the AddState method, because we don't want to remove the previous state.
        // I haven't tested going back yet so exit the game and run it again if you want to go back to the previous state.
        if (_data->inputs.IsButtonClicked(buttons->play, Mouse::Left, _data->window)) {
            this->notify("Switching to game", "System");
            _data->stateMachine.AddState(StateRef(new GameScreen(_data)), false, _data->log);
        } else if (_data->inputs.IsButtonClicked(buttons->editMap, Mouse::Left, _data->window)) {
            this->notify("Switching to map editor", "System");
        } else if (_data->inputs.IsButtonClicked(buttons->editCharacter, Mouse::Left, _data->window)) {
            this->notify("Switching to character editor", "System");
        } else if (_data->inputs.IsButtonClicked(buttons->load, Mouse::Left, _data->window)) {
            this->notify("Switching to load menu", "System");
        } else if (_data->inputs.IsButtonClicked(buttons->options, Mouse::Left, _data->window)) {
            this->notify("Switching to options menu", "System");
        } else if (_data->inputs.IsButtonClicked(buttons->quit, Mouse::Left, _data->window)) {
            _data->window.close();
        }



    }
}

void MainMenu::SetButtons() {

    Font& font = _data->assets.GetFont("My Font");
    Vector2f position = Vector2f(_data->window.getSize().x/2.0f, _data->window.getSize().y/3.4f);

    GenerateButton(font, "Play", buttons->play, buttons->playText, position);
    GenerateButton(font, "Edit Map", buttons->editMap, buttons->editMapText, position + Vector2f(0, 100));
    GenerateButton(font, "Edit Character", buttons->editCharacter, buttons->editCharacterText, position + Vector2f(0, 200));
    GenerateButton(font, "Load Map", buttons->load, buttons->loadText, position + Vector2f(0, 300));
    GenerateButton(font, "Options", buttons->options, buttons->optionsText, position + Vector2f(0, 400));
    GenerateButton(font, "Quit", buttons->quit, buttons->quitText, position + Vector2f(0, 500));

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
void MainMenu::GenerateButton(const Font &font, const string& name, RectangleShape &button, Text &buttonText, Vector2f position) {

    Vector2f size = Vector2f(300, 50);
    button.setSize(size);
    button.setOrigin(size.x/2.0f, size.y/2.0f);
    button.setPosition(position);
    button.setFillColor(Color(0x3f3a4daa));
    // TODO Maybe add a hover color



    buttonText.setString(name);
    buttonText.setFont(font);
    buttonText.setCharacterSize(MENU_CHAR_SIZE);
    buttonText.setFillColor(Color::White);
    FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.width/2.0f, textBounds.height/2.0f);
    buttonText.setPosition(position.x + size.x/2.0f, position.y + size.y/2.0f);
    buttonText.setPosition(position);

}
