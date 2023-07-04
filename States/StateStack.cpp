//
// Created by kawre on 25.05.2023.
//

#include "../Headers/StateStack.h"
#include "../Headers/MenuState.h"

void StateStack::pushState(std::unique_ptr<State> state)
{
    states.push(std::move(state));
}

State& StateStack::currentState()
{
    return *states.top();
}

void StateStack::handleEvents(sf::Event& e)
{
    currentState().handleEvents(e);
}

void StateStack::update()
{
    currentState().update();
}

void StateStack::render()
{
    currentState().render();
}

void StateStack::menuState()
{
    while (!states.empty() && dynamic_cast<MenuState*>(states.top().get()) == nullptr)
        states.pop();
}
