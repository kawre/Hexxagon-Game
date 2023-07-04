//
// Created by kawre on 23.05.2023.
//

#ifndef HEXXAGON_MAINMENUSTATE_H
#define HEXXAGON_MAINMENUSTATE_H

#include <stack>
#include "State.h"
#include "TextBox.h"
#include "Button.h"
#include "StateStack.h"

class MenuState : public State
{
 private:
    sf::RenderWindow* window;
    sf::Font font;
    StateStack& state;

    std::vector<Button> buttons;
    TextBox logo;
    Button button;

 public:
    MenuState(sf::RenderWindow*, StateStack&);

    void handleEvents(sf::Event& e) override;
    void update() override;
    void render() override;

    void initButton();
    void initButtons();
};

#endif //HEXXAGON_MAINMENUSTATE_H
