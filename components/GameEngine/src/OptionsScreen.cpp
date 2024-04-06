//
// Created by minaei on 4/5/2024.
//

#include "OptionsScreen.h"
OptionsScreen::OptionsScreen(MainDataRef data) : _data(data) {}

void OptionsScreen::Init() {
    this->_data->assets.LoadTexture("Menu Background", MENU_BG_IMAGE_PATH);
    this->_data->assets.LoadFont("Font", FONT_PATH);
    _bg.setTexture(this->_data->assets.GetTexture("Menu Background"));
    _bg.setTextureRect(IntRect(0,0, this->_data->window.getSize().x, this->_data->window.getSize().y));

    SetButtons();

}

void OptionsScreen::Update(float deltaTime) {
}

void OptionsScreen::Draw(float deltaTime) {
    _data->window.clear();
    _data->window.draw(_bg);

    _data->window.draw(buttons->mute);
    _data->window.draw(buttons->muteText);
    _data->window.draw(buttons->back);
    _data->window.draw(buttons->backText);

    // add our names
    _data->window.display();

}

void OptionsScreen::HandleInput() {
    Event event{};
    while (this->_data->window.pollEvent(event)) {
        if (Event::Closed == event.type) {
            this->_data->window.close();
        }

        if (_data->inputs.IsButtonClicked(buttons->mute, Mouse::Left, _data->window)) {
            this->notify("Muting the music", "System");
            _data->music.setVolume(0.f);
        }
        else if (_data->inputs.IsButtonClicked(buttons->back, Mouse::Left, _data->window)) {
            this->notify("Returning to the Main menu", "System");
            _data->stateMachine.RemoveState();
        }
    }
}

void OptionsScreen::SetButtons() {

    Font& font = _data->assets.GetFont("My Font");
    Vector2f position = Vector2f(_data->window.getSize().x/2.0f, _data->window.getSize().y/3.4f);

    GenerateButton(font, "Mute", buttons->mute, buttons->muteText, position);
    GenerateButton(font, "Back", buttons->back, buttons->backText, position + Vector2f(0, 100));


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
void OptionsScreen::GenerateButton(const Font &font, const string& name, RectangleShape &button, Text &buttonText, Vector2f position) {

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
