/**
 * @file MainMenu.cpp
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#include "MainMenu.h"
#include "GameScreen.h"
#include "OptionsScreen.h"
#include "MapCreator.h"

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
    _data->window.draw(buttons->createCharacter);
    _data->window.draw(buttons->createCharacterText);
    _data->window.draw(buttons->editCharacter);
    _data->window.draw(buttons->editCharacterText);
    _data->window.draw(buttons->load);
    _data->window.draw(buttons->loadText);
    _data->window.draw(buttons->options);
    _data->window.draw(buttons->optionsText);
    _data->window.draw(buttons->quit);
    _data->window.draw(buttons->quitText);

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

void MainMenu::HandleInput() {
    Event event{};
    while (this->_data->window.pollEvent(event)) {
        if (Event::Closed == event.type) {
            this->_data->window.close();
        }
        // TODO Implement the button click handling according to your needs
        // For transition to another state use the WelcomeScreen.cpp as an example. However,
        // don't pass a true to the AddState method, because we don't want to remove the previous state.
        // I haven't tested going back yet so exit the game and run it again if you want to go back to the previous state.

        //Play
        if (_data->inputs.IsButtonClicked(buttons->play, Mouse::Left, _data->window)) {
            this->notify("Switching to game", "System");
            _data->stateMachine.AddState(StateRef(new GameScreen(_data)), false, _data->log);
        }

        //Map Creator
        else if (_data->inputs.IsButtonClicked(buttons->editMap, Mouse::Left, _data->window)) {
            this->notify("Switching to map editor", "System");
            _data->stateMachine.AddState(StateRef(new MapCreator(_data)), false, _data->log);
        }

        //Character Creator
        else if (_data->inputs.IsButtonClicked(buttons->editCharacter, Mouse::Left, _data->window)) {
            this->notify("Switching to character editor", "System");
            _data->stateMachine.AddState(StateRef(new CharacterCreator(_data)), false, _data->log);
        }

        //Load Previous Game
        else if (_data->inputs.IsButtonClicked(buttons->load, Mouse::Left, _data->window)) {
            this->notify("Switching to load menu", "System");
        } else if (_data->inputs.IsButtonClicked(buttons->options, Mouse::Left, _data->window)) {
            this->notify("Switching to options menu", "System");
            _data->stateMachine.AddState(StateRef(new OptionsScreen(_data)), false, _data->log);
        } else if (_data->inputs.IsButtonClicked(buttons->quit, Mouse::Left, _data->window)) {
            this->notify("Quitting game", "System");
            _data->window.close();
        }






    }
}

void MainMenu::SetButtons() {

    int nbButtons = 5;

    Font& font = _data->assets.GetFont("My Font");
    Vector2f position = Vector2f(_data->window.getSize().x/2.0f, _data->window.getSize().y/6.0f);

    //This is the spacing between the buttons
    //Changed it to be a seventh of the window height to make it less hard coded
    Vector2f spacing = Vector2f(0, _data->window.getSize().y/6.0f);

    GenerateButton(font, "Play", buttons->play, buttons->playText, position);
    GenerateButton(font, "Edit Map", buttons->editMap, buttons->editMapText, position + Vector2f(0, spacing.y));
    GenerateButton(font, "Edit Character", buttons->editCharacter, buttons->editCharacterText, position + Vector2f(0, 2*spacing.y));

    GenerateButton(font, "Options", buttons->options, buttons->optionsText, position + Vector2f(0, 3*spacing.y));
    GenerateButton(font, "Quit", buttons->quit, buttons->quitText, position + Vector2f(0, 4* spacing.y));


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
