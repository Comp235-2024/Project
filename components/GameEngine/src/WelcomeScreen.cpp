/**
 * @file WelcomeScreen.cpp
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#include "WelcomeScreen.h"
#include "MainMenu.h"



WelcomeScreen::WelcomeScreen(MainDataRef data) : _data(data) {}
void WelcomeScreen::Init() {
    this->_data->assets.LoadTexture("Welcome Screen Background", WELCOME_BG_IMAGE_PATH);
    this->_data->assets.LoadFont("Font", FONT_PATH);
    _bg.setTexture(this->_data->assets.GetTexture("Welcome Screen Background"));
    _bg.setTextureRect(IntRect(0,0, this->_data->window.getSize().x, this->_data->window.getSize().y));

    string message = "Hello and welcome.";
    text.setFont(_data->assets.GetFont("Font"));
    text.setString(message);
    text.setCharacterSize(WELCOME_CHAR_SIZE);
    text.setFillColor(Color::White);

    FloatRect spriteBounds = _bg.getGlobalBounds();
    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.width/2.0f, textBounds.height/2.0f);
    text.setPosition(textBounds.left + spriteBounds.width/2.0f, textBounds.top + spriteBounds.height/3.0f);
}

void WelcomeScreen::Update(float deltaTime) {
    if (_clock.getElapsedTime().asSeconds() > WELCOME_STATE_DURATION) {
        // Switch to main menu
        this->notify("Switching to main menu", "System");
        _data->stateMachine.AddState(StateRef(new MainMenu(_data)), true, _data->log);
    }
}

void WelcomeScreen::Draw(float deltaTime) {
    _data->window.clear();
    _data->window.draw(_bg);
    _data->window.draw(text);

    // add our names
    _data->window.display();

}

void WelcomeScreen::HandleInput() {
    Event event{};
    while (_data->window.pollEvent(event)) {
        if (Event::Closed == event.type) {
            _data->window.close();
        }
    }
}

