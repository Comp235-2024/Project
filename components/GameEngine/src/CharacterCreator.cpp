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
    this->_data->assets.LoadFont("Font", FONT_PATH);
    _bg.setTexture(this->_data->assets.GetTexture("Menu Background"));
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

}

void CharacterCreator::HandleInput() {
    Event event{};
    while (this->_data->window.pollEvent(event)) {
        if (Event::Closed == event.type) {
            this->_data->window.close();
        }
        if (_data->inputs.IsSpriteClicked(buttons->dwarf, sf::Mouse::Left, _data->window)) {
//            CreateCharacter("Bully");
//            CharacterCreator::DisplayCreationMessage("Nimble Character Created");
            this->notify("Creating dwarf character", "System");
            //_data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
            _data->player.textureName = "dwarf_m";
            this->notify("Returning to the Main menu", "System");
            _data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
        }
        else if (_data->inputs.IsSpriteClicked(buttons->elf, sf::Mouse::Left, _data->window)) {

            this->notify("Creating elf character", "System");
            //_data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
            _data->player.textureName = "elf_f";
            this->notify("Returning to the Main menu", "System");
            //_data->stateMachine.RemoveState();
            _data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
        }
        else if (_data->inputs.IsSpriteClicked(buttons->elf, sf::Mouse::Left, _data->window)) {

            this->notify("Creating lizard character", "System");
            //_data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
            _data->player.textureName = "lizard_f";
            this->notify("Returning to the Main menu", "System");
            //_data->stateMachine.RemoveState();
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


    _data->window.draw(buttons->dwarf);
    _data->window.draw(buttons->elf);
    _data->window.draw(buttons->lizard);
    _data->window.draw(buttons->next);
    _data->window.draw(buttons->back);


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

    GenerateButton(buttons->dwarf, position, this->_data->assets.GetTexture("dwarf_m"));
    GenerateButton(buttons->elf, position + Vector2f(0,20), this->_data->assets.GetTexture("elf_f"));
    GenerateButton(buttons->lizard, position + Vector2f(0,40), this->_data->assets.GetTexture("lizard_f"));
    GenerateButton(buttons->next, position + Vector2f(0,60), this->_data->assets.GetTexture("nextButton"));
    GenerateButton(buttons->back, position + Vector2f(0,80), this->_data->assets.GetTexture("backButton"));

//    GenerateButton(font, "Create Nimble ", buttons->CreateBully, buttons->CreateBullyText, position);
//    GenerateButton(font, "Create Bully", buttons->CreateNimble, buttons->CreateNimbleText, position + Vector2f(0, 100));
//    GenerateButton(font, "Create Tank", buttons->CreateTank, buttons->CreateTankText, position + Vector2f(0, 200));

}

void CharacterCreator::GenerateButton(const Font &font, const string& name, RectangleShape &button, Text &buttonText, Vector2f position) {

    Vector2f size = Vector2f(300, 50);
    button.setSize(size);
    button.setOrigin(size.x/2.0f, size.y/2.0f);
    button.setPosition(position);
    button.setFillColor(Color(0x3f3a4daa));
    buttonText.setString(name);
    buttonText.setFont(font);
    buttonText.setCharacterSize(MENU_CHAR_SIZE);
    buttonText.setFillColor(Color::White);
    FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.width/2.0f, textBounds.height/2.0f);
    buttonText.setPosition(position.x + size.x/2.0f, position.y + size.y/2.0f);
    buttonText.setPosition(position);

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
void CharacterCreator::GenerateButton(Sprite& button, Vector2f position, Texture& texture) {

    Vector2f size = Vector2f(50, 50);
    //button.setSize(size);
    button.setOrigin(size.x/1.0f, size.y/1.0f);
    button.setPosition(position);
    // TODO Maybe add a hover color
    button.setTexture(texture);
}