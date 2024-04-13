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

    _data->window.draw(buttons->back);
    _data->window.draw(buttons->music1);
    _data->window.draw(buttons->music2);
    _data->window.draw(buttons->music3);
    _data->window.draw(buttons->music4);

    _data->window.draw(buttons->music);
    _data->window.draw(buttons->musicText);
    // add our names
    _data->window.display();

}

void OptionsScreen::HandleInput() {
    Event event{};
    while (this->_data->window.pollEvent(event)) {
        if (Event::Closed == event.type) {
            this->_data->window.close();
        }

        if (this->_data->inputs.IsSpriteClicked(buttons->mute, Mouse::Left, _data->window)) {
            handleMusic();

        }
        else if (this->_data->inputs.IsSpriteClicked(buttons->back, Mouse::Left, _data->window)) {
            this->notify("Returning to the Main menu", "System");
            _data->stateMachine.RemoveState();
        }
        else if (this->_data->inputs.IsSpriteClicked(buttons->music1, Mouse::Left, _data->window)) {
            this->notify("Play music 1", "System");
            changeMusic(MUSIC1_PATH);
        }
        else if (this->_data->inputs.IsSpriteClicked(buttons->music2, Mouse::Left, _data->window)) {
            this->notify("Play music 2", "System");
            changeMusic(MUSIC2_PATH);
        }
        else if (this->_data->inputs.IsSpriteClicked(buttons->music3, Mouse::Left, _data->window)) {
            this->notify("Play music 3", "System");
            changeMusic(MUSIC3_PATH);
        }
        else if (this->_data->inputs.IsSpriteClicked(buttons->music4, Mouse::Left, _data->window)) {
            this->notify("Play music 4", "System");
            changeMusic(MUSIC4_PATH);
        }
    }
}

void OptionsScreen::changeMusic(string fileName) {
    bool musicOff = false;
    if(_data->music.getVolume() < 1.f) {
        musicOff = true;
    }
    if (!_data->music.openFromFile(fileName))
    {
        cerr << "Error while loading background music file" << endl;
    }
    else {
        if(musicOff) {
            _data->music.setVolume(0.f);
        }
        else {
            _data->music.setVolume(DEFAULT_MUSIC_VOL);
        }
        _data->music.setLoop(true);
        _data->music.play();
    }
}

void OptionsScreen::handleMusic() {
    if(_data->music.getVolume() < 1.f) {
        buttons->mute.setTexture(this->_data->assets.GetTexture("musicOn"));
        this->notify("Unmuting the music", "System");
        _data->music.setVolume(DEFAULT_MUSIC_VOL);
    }
    else {
        buttons->mute.setTexture(this->_data->assets.GetTexture("musicOff"));
        this->notify("Muting the music", "System");
        _data->music.setVolume(0.f);
    }

}

void OptionsScreen::SetButtons() {

    Font& font = _data->assets.GetFont("My Font");
    Vector2f position = Vector2f(_data->window.getSize().x/5.0f, _data->window.getSize().y/5.0f);
    if(_data->music.getVolume() < 1.f) {
        GenerateButton(buttons->mute, position, this->_data->assets.GetTexture("musicOff"));
    }
    else{
        GenerateButton(buttons->mute, position, this->_data->assets.GetTexture("musicOn"));
    }
    GenerateButton(buttons->back, position + Vector2f(0, _data->window.getSize().y/5.0f*3), this->_data->assets.GetTexture("backButton"));

    GenerateButton(buttons->music1, position + Vector2f(_data->window.getSize().x/5.0f*3, _data->window.getSize().y/8.0f), this->_data->assets.GetTexture("music1"));
    GenerateButton(buttons->music2, position + Vector2f(_data->window.getSize().x/5.0f*3, _data->window.getSize().y/8.0f*2), this->_data->assets.GetTexture("music2"));
    GenerateButton(buttons->music3, position + Vector2f(_data->window.getSize().x/5.0f*3, _data->window.getSize().y/8.0f*3), this->_data->assets.GetTexture("music3"));
    GenerateButton(buttons->music4, position + Vector2f(_data->window.getSize().x/5.0f*3, _data->window.getSize().y/8.0f*4), this->_data->assets.GetTexture("music4"));
    //GenerateButton(font, "Music: ", buttons->music, buttons->musicText, position + Vector2f(_data->window.getSize().x/5.0f*3, _data->window.getSize().y/10.0f));

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
void OptionsScreen::GenerateButton(Sprite& button, Vector2f position, Texture& texture) {

    Vector2f size = Vector2f(50, 50);
    //button.setSize(size);
    button.setOrigin(size.x/1.0f, size.y/1.0f);
    button.setPosition(position);
    // TODO Maybe add a hover color
    button.setTexture(texture);
}

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