//
// Created by Khalil Azaiez on 2024-03-30.
//

#include "CharacterCreator.h"
#include "BullyBuilder.h"
#include "NimbleBuilder.h"
#include "TankBuilder.h"
#include "MapObserver.h"
#include "GameScreen.h"

CharacterCreator::CharacterCreator(MainDataRef data) : _data(data) {}

void CharacterCreator::Init() {
    this->_data->assets.LoadTexture("Game Background", GAME_BG_IMAGE_PATH);
    this->_data->assets.LoadFont("Font", FONT_PATH);
    _bg.setTexture(this->_data->assets.GetTexture("Game Background"));
    _bg.setTextureRect(IntRect(0,0, this->_data->window.getSize().x, this->_data->window.getSize().y));
    SetButtons();
}

void CharacterCreator::DisplayCreationMessage(const std::string& message) {
    // Set up a text object to display the message
    sf::Text creationMessage;
    creationMessage.setFont(_data->assets.GetFont("My Font"));
    creationMessage.setString(message);
    creationMessage.setCharacterSize(MENU_CHAR_SIZE); // Use the same size as your menu items for consistency
    creationMessage.setFillColor(sf::Color::White);

    // Center the message on the screen
    sf::FloatRect messageBounds = creationMessage.getLocalBounds();
    creationMessage.setOrigin(messageBounds.width / 2, messageBounds.height / 2);
    creationMessage.setPosition(_data->window.getSize().x / 2.0f, _data->window.getSize().y / 2.0f);

    // Draw the message
    _data->window.clear();
    _data->window.draw(_bg); // Draw the background first
    _data->window.draw(creationMessage); // Draw the message on top
    _data->window.display();

    // Wait for a short time to display the message
    sf::sleep(sf::seconds(1.5)); // For example, wait for 1.5 seconds
}

void CharacterCreator::HandleInput() {
    Event event{};
    while (this->_data->window.pollEvent(event)) {
        if (Event::Closed == event.type) {
            this->_data->window.close();
        }
        if (_data->inputs.IsButtonClicked(buttons->CreateBully, sf::Mouse::Left, _data->window)) {
            CreateCharacter("Bully");
            CharacterCreator::DisplayCreationMessage("Nimble Character Created");
            this->notify("Creating Bully character", "System");
            _data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
        } else if (_data->inputs.IsButtonClicked(buttons->CreateNimble, sf::Mouse::Left, _data->window)) {
            CreateCharacter("Nimble");
            CharacterCreator::DisplayCreationMessage("Bully Character Created");
            this->notify("Creating Nimble character", "System");
            _data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
        } else if (_data->inputs.IsButtonClicked(buttons->CreateTank, sf::Mouse::Left, _data->window)) {
            CreateCharacter("Tank");
            CharacterCreator::DisplayCreationMessage("Tank Character Created");
            this->notify("Creating Tank character", "System");
            _data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
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
        Character bully(1);
        bullyBuilder.buildAbilityScores();
        bullyBuilder.buildHitPoints(bully);
        bully.textureName = 'lizard_f';
        this->_data->player = bully;

    } else if (type == "Nimble") {
        NimbleBuilder nimbleBuilder;
        Character nimble(1);
        nimbleBuilder.buildAbilityScores();
        nimbleBuilder.buildHitPoints(nimble);
        this->_data->player = nimble;

    } else if (type == "Tank") {
        TankBuilder TankBuilder;
        Character tank(1);
        TankBuilder.buildAbilityScores();
        TankBuilder.buildHitPoints(tank);
        this->_data->player = tank;
    }

    // Assume _characterSprite is an sf::Sprite attribute of CharacterCreator
    //_characterSprite.setTexture(_data->assets.GetTexture(type + " Icon"));
    // Set position, scale, etc., based on grid layout
}

void CharacterCreator::Draw(float deltaTime) {
    _data->window.clear();
    _data->window.draw(_bg);

    _data->window.draw(buttons->CreateBully);
    _data->window.draw(buttons->CreateBullyText);
    _data->window.draw(buttons->CreateNimble);
    _data->window.draw(buttons->CreateNimbleText);
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

    GenerateButton(font, "Create Nimble ", buttons->CreateBully, buttons->CreateBullyText, position);
    GenerateButton(font, "Create Bully", buttons->CreateNimble, buttons->CreateNimbleText, position + Vector2f(0, 100));
    GenerateButton(font, "Create Tank", buttons->CreateTank, buttons->CreateTankText, position + Vector2f(0, 200));

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
