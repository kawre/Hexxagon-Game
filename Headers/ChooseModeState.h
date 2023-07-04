//
// Created by kawre on 25.05.2023.
//

#ifndef _CHOOSEMODESTATE_H_
#define _CHOOSEMODESTATE_H_

#include "State.h"
#include "Button.h"
#include "StateStack.h"
#include "RadioButton.h"
#include <stack>

enum class Against
{
    PLAYER, COMPUTER
};

class ChooseModeState : public State
{
 private:
    sf::RenderWindow* window;
    StateStack& state;
    Against against;
    Button button;

    RadioButton radioButton;
    std::vector<RadioButton> radioButtons;

 public:
    ChooseModeState(sf::RenderWindow* window, StateStack&);

    // init
    void initButton();
    void initRadioButtons();

    // functions
    void deFocusRadioButtons();

    //
    void handleEvents(sf::Event& e) override;
    void update() override;
    void render() override;
};

#endif //_CHOOSEMODESTATE_H_
