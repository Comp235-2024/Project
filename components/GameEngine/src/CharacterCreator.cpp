//
// Created by Khalil Azaiez on 2024-03-30.
//

#include "CharacterCreator.h"
#include "BullyBuilder.h"
#include "NimbleBuilder.h"
#include "TankBuilder.h"


CharacterCreator::CharacterCreator(MainDataRef data) : _data(data) {}

void CharacterCreator::Init() {
    this->_data->assets.LoadTexture("Game Background", GAME_BG_IMAGE_PATH);
    this->_data->assets.LoadFont("Font", FONT_PATH);
    _bg.setTexture(this->_data->assets.GetTexture("Game Background"));
    _bg.setTextureRect(IntRect(0,0, this->_data->window.getSize().x, this->_data->window.getSize().y));
    SetButtons();
}

void CharacterCreator::HandleInput() {
    Event event{};
    while (this->_data->window.pollEvent(event)) {
        if (Event::Closed == event.type) {
            this->_data->window.close();
        }
        if (_data->inputs.IsButtonClicked(buttons->CreateBully, sf::Mouse::Left, _data->window)) {
            CreateCharacter("Bully");
        } else if (_data->inputs.IsButtonClicked(buttons->CreateNimble, sf::Mouse::Left, _data->window)) {
            CreateCharacter("Nimble");
        } else if (_data->inputs.IsButtonClicked(buttons->CreateTank, sf::Mouse::Left, _data->window)) {
            CreateCharacter("Tank");
        }
    }
}

void CharacterCreator::Update(float deltaTime) {
    // Update logic if needed
}

void CharacterCreator::CreateCharacter(const std::string& type) {
    // Instantiate the character using the selected builder
    // This is a simplified example; you might need to integrate with your game's character management system
    Character* newCharacter = nullptr;
    if (type == "Bully") {
        BullyBuilder bullyBuilder;
        bullyBuilder.buildAbilityScores();
        newCharacter = bullyBuilder.getCharacter();
    } else if (type == "Nimble") {
        NimbleBuilder nimbleBuilder;
        nimbleBuilder.buildAbilityScores();
        newCharacter = nimbleBuilder.getCharacter();
    } else if (type == "Tank") {
        TankBuilder TankBuilder;
        TankBuilder.buildAbilityScores();
        newCharacter = TankBuilder.getCharacter();
    }

    // Assume _characterSprite is an sf::Sprite attribute of CharacterCreator
    //_characterSprite.setTexture(_data->assets.GetTexture(type + " Icon"));
    // Set position, scale, etc., based on grid layout
}

void CharacterCreator::Draw(float deltaTime) {
    _data->window.clear();
    _data->window.draw(_bg);

    _data->window.draw(buttons->CreateNimble);
    _data->window.draw(buttons->CreateNimbleText);
    _data->window.draw(buttons->CreateBully);
    _data->window.draw(buttons->CreateBullyText);
    _data->window.draw(buttons->CreateTank);
    _data->window.draw(buttons->CreateTankText);

    _data->window.display();

}

void CharacterCreator::generateMapTexture() {
    _mapTexture.clear(Color::Transparent);
    //TODO implement complex maps and their rendering

    //

    //    mapObserver.updateMapOnly(&_mapTexture);
    mapObserver.update();

    _mapTexture.display();



}

void CharacterCreator::SetButtons() {

    Font& font = _data->assets.GetFont("My Font");
    Vector2f position = Vector2f(_data->window.getSize().x/2.0f, _data->window.getSize().y/3.4f);

    GenerateButton(font, "Play", buttons->CreateNimble, buttons->CreateNimbleText, position);
    GenerateButton(font, "Edit Map", buttons->CreateBully, buttons->CreateBullyText, position + Vector2f(0, 100));
    GenerateButton(font, "Create Character", buttons->CreateTank, buttons->CreateTankText, position + Vector2f(0, 200));


}

void CharacterCreator::GenerateButton(const Font &font, const string& name, RectangleShape &button, Text &buttonText, Vector2f position) {

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
