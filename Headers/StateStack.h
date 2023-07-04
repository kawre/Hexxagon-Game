//
// Created by kawre on 25.05.2023.
//

#ifndef _STATESTACK_H_
#define _STATESTACK_H_

#include <iostream>
#include <memory>
#include <stack>
#include "State.h"

class StateStack : public State
{
 private:
    std::stack<std::unique_ptr<State>> states;

 public:
    void pushState(std::unique_ptr<State> state);

    // getters
    State& currentState();

    /**
     * @brief usuwa elementy z góry stosu, dopóki nie znajdzie stanu menu
     * @return stan menu
     */
    void menuState();

    void handleEvents(sf::Event& e) override;
    void update() override;
    void render() override;
};

#endif //_STATESTACK_H_
