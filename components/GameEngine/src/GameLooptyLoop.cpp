/**
 * @file GameLooptyLoop.cpp
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#include "GameLooptyLoop.h"
#include "WelcomeScreen.h"
#include "MainMenu.h"
#include "Log/include/LogObserver.h"



GameLooptyLoop::GameLooptyLoop(int width, int height, const string& title) {

    _data->window.create(VideoMode(width, height), title, Style::Close | Style::Titlebar);
    _data->window.setFramerateLimit(60);
//    _data->stateMachine.AddState(StateRef(new MainMenu(_data)), false);
    _data->assets.LoadFont("My Font", FONT_PATH);

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
