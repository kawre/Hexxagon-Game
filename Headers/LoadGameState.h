//
// Created by kawre on 02.06.2023.
//

#ifndef _LOADGAMESTATE_H_
#define _LOADGAMESTATE_H_

#include "State.h"
#include "StateStack.h"
#include "Button.h"
#include "HexagonShape.h"

class LoadGameState : public State
{
 private:
    sf::RenderWindow* window;
    StateStack& state;
    Button quitButton;
    Button loadButton;

    sf::String input;
    sf::Text text;
    sf::RectangleShape textBg;

 public:
    LoadGameState(sf::RenderWindow* window, StateStack& state);

    void initQuitButton();

    void handleEvents(sf::Event& e) override;
    void update() override;
    void render() override;
    void initInputText();
    void initLoadButton();
    std::unordered_map<std::string, HexagonShape> loadState();
};

#endif //_LOADGAMESTATE_H_
