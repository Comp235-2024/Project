/**
 * @file GameLooptyLoop.cpp
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#include "GameLooptyLoop.h"
#include "WelcomeScreen.h"
#include "MainMenu.h"
#include "../../Log/include/LogObserver.h"
#include <format>



GameLooptyLoop::GameLooptyLoop(int width, int height, const string& title) {

    _data->window.create(VideoMode(width, height), title, Style::Close | Style::Titlebar);
    _data->window.setFramerateLimit(60);
//    _data->stateMachine.AddState(StateRef(new MainMenu(_data)), false);
    _data->assets.LoadFont("My Font", FONT_PATH);

    // Load floor textures
    string path = "../../assets/images/frames/floor_1.png";
    for (int i = 1; i < 9; ++i) {
        _data->assets.LoadTexture(format("floor_{}", i), format("../../assets/images/frames/floor_{}.png", i));
    }
    _data->assets.LoadTexture("knight", "../../assets/images/frames/knight_m_idle_anim_f0.png");
    _data->assets.LoadTexture("wizard", "../../assets/images/frames/wizzard_m_idle_anim_f0.png");
    //tiny_zombie, skelet, pumpkin_dude, orc_warrior, knight_m, wizard_f, orc_shaman, orge, necromancer, masked_orc, lizard, imp, goblin, elf_f, dwarf_m, doc, big_demon, angel
    string characters[] = {"tiny_zombie", "skelet", "pumpkin_dude", "orc_warrior", "knight_m", "wizzard_f", "orc_shaman", "ogre", "masked_orc", "lizard_f", "imp", "goblin", "elf_f", "dwarf_m", "doc", "big_demon", "angel"};
    for (auto &character : characters) {
        _data->assets.LoadTexture(character, format("../../assets/images/frames/{}_idle_anim_f0.png", character));
    }

    _data->assets.LoadTexture("wall_mid", WALL_IMAGE_PATH);
    _data->assets.LoadTexture("crate", CHEST_IMAGE_PATH);
    _data->assets.LoadTexture("door", DOOR_IMAGE_PATH);
    _data->assets.LoadTexture("lever", LEVER_IMAGE_PATH);

    _data->log = new LogObserver("log.txt");
//    log->enabledModules.disableAll();
    if(_data->log->enabledModules.system) {
        cout << "Log observer attached to all modules" << endl;
        _data->assets.attach(_data->log);
        _data->stateMachine.attach(_data->log);
        _data->stateMachine.AddState(StateRef(new WelcomeScreen(_data)), false, _data->log);
    } else {
        _data->stateMachine.AddState(StateRef(new WelcomeScreen(_data)), false);
    }

    Run();
}

void GameLooptyLoop::Run() {
    float newTime, frameTime, interpolation;

    float currentTime = _clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (_data->window.isOpen()){
        _data->stateMachine.ProcessStateChanges();

        newTime = _clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if (frameTime > 0.25f) {
            frameTime = 0.25f;
        }
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= deltaTime) {
            _data->stateMachine.GetActiveState()->HandleInput();
            _data->stateMachine.GetActiveState()->Update(deltaTime);
            accumulator -= deltaTime;
        }

        interpolation = accumulator / deltaTime;
        _data->stateMachine.GetActiveState()->Draw(interpolation);

    }



}
