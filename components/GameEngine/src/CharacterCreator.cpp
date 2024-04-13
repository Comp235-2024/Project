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
        if (_data->inputs.IsSpriteClicked(buttons->next, sf::Mouse::Left, _data->window)) {
            if(index == 2) {
                index = 0;
            }
            else {
                index ++;
            }
            Draw(0.0);
        }
        else if (_data->inputs.IsSpriteClicked(buttons->back, sf::Mouse::Left, _data->window)) {
            if(index == 0) {
                index = 2;
            }
            else {
                index --;
            }
            Draw(0.0);

        }

        else if (_data->inputs.IsButtonClicked(buttons->choose, Mouse::Left, _data->window)) {
            this->CreateCharacter();
        }
    }
}

void CharacterCreator::Update(float deltaTime) {

}

void CharacterCreator::CreateCharacter() {
    if(index == 0) {
        this->notify("Creating dwarf character", "System");
        _data->player.textureName = "dwarf_m";
        this->notify("Returning to the Main menu", "System");
        _data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
    }
    else if (index == 1) {
        this->notify("Creating elf character", "System");
        _data->player.textureName = "elf_f";
        this->notify("Returning to the Main menu", "System");
        _data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
    }
    else if(index == 2) {
        this->notify("Creating lizard character", "System");
        _data->player.textureName = "lizard_f";
        this->notify("Returning to the Main menu", "System");
        _data->stateMachine.AddState(StateRef(new MainMenu(_data)), false, _data->log);
    }

}

void CharacterCreator::Draw(float deltaTime) {
    _mapTexture.clear(Color::Transparent);
    _data->window.clear(Color::Transparent);

    _data->window.draw(_bg);

    _data->window.draw(buttons->choose);
    _data->window.draw(buttons->chooseText);


    _data->window.draw(buttons->panel);
    _data->window.draw(buttons->next);
    _data->window.draw(buttons->back);

    if(index == 0)
        _data->window.draw(buttons->dwarf);
    else if(index == 1)
        _data->window.draw(buttons->elf);
    else if(index == 2)
        _data->window.draw(buttons->lizard);



    _data->window.display();

}

void CharacterCreator::generateMapTexture() {
    mapObserver.update();
    _mapTexture.display();
}

void CharacterCreator::SetButtons() {
    Font& font = _data->assets.GetFont("My Font");
    Vector2f position = Vector2f(_data->window.getSize().x/2.0f, _data->window.getSize().y/2.f);

    GenerateButton(buttons->dwarf, position + Vector2f(-50,-300), this->_data->assets.GetTexture("dwarf_m"), 6, 6);
    GenerateButton(buttons->elf, position + Vector2f(-50,-300), this->_data->assets.GetTexture("elf_f"), 6, 6);
    GenerateButton(buttons->lizard, position + Vector2f(-50,-300), this->_data->assets.GetTexture("lizard_f"), 6, 6);

    GenerateButton(buttons->panel, position + Vector2f(-200,-400), this->_data->assets.GetTexture("panel"), 3, 3);
    GenerateButton(buttons->next, position + Vector2f(60,-130), this->_data->assets.GetTexture("nextButton"), 1, 1);
    GenerateButton(buttons->back, position + Vector2f(-200,-130), this->_data->assets.GetTexture("backButton"), 1, 1);

    GenerateButton(font, "Choose this!", buttons->choose, buttons->chooseText, position + Vector2f(0,20));
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
void CharacterCreator::GenerateButton(Sprite& button, Vector2f position, Texture& texture, int x, int y) {

    Vector2f size = Vector2f(x, y);
    button.setScale(size);
    button.setOrigin(size.x/2.0f, size.y/2.0f);
    button.setPosition(position);
    // TODO Maybe add a hover color
    button.setTexture(texture);
}