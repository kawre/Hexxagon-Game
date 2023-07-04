//
// Created by kawre on 23.05.2023.
//

#include "../Headers/MenuState.h"
#include "../Static/Theme.h"
#include "../Headers/GamePlayState.h"
#include "../Headers/BestScoresState.h"
#include "../Headers/LoadGameState.h"
#include <SFML/Graphics.hpp>
#include <vector>

using std::pair, std::vector, std::function;

MenuState::MenuState(sf::RenderWindow* window, StateStack& state)
    : window(window),
      state(state),
      logo(80, Theme::WhitePawn)
{
    initButtons();
}

void MenuState::handleEvents(sf::Event& e)
{
    for (auto& btn : buttons)
        btn.handleInput(window, e);
}

void MenuState::update()
{
}

void MenuState::render()
{
    this->window->clear(Theme::Background);

    for (auto& btn : buttons)
        btn.drawTo(window);
    logo.drawTo(window);

    this->window->display();
}

void MenuState::initButton()
{
    button.setFont(Theme::Font);

    button.setTextSize(40);
    button.setPadding({ 30, 15 });
    button.setText("INIT");
}

void MenuState::initButtons()
{
    initButton();

    vector<pair<sf::String, function<void()>>> texts = {
        pair("NEW GAME", [&]() {
            state.pushState(std::make_unique<ChooseModeState>(window, state));
        }),
        pair("LOAD GAME", [&]() {
            state.pushState(std::make_unique<LoadGameState>(window, state));
        }),
        pair("BEST SCORES", [&]() {
            state.pushState(std::make_unique<BestScoresState>(window, state));
        }),
    };

    float yCenter = window->getSize().y / 2.f;
    float btnHeight = button.getSize().y;
    float gap = 50;
    float yTop = yCenter - ((btnHeight + gap) * (texts.size() / 2));

    for (int i = 0; i < texts.size(); i++)
    {
        auto pair = texts.at(i);
        button.clearCallbacks();
        button.setText(pair.first);
        button.addCallback(sf::Event::MouseButtonPressed, sf::Mouse::Left, pair.second);
        button.setPosition({ window->getSize().x / 2.f, yTop + (i * (btnHeight + gap)) });
        buttons.push_back(button);
    }

    logo.setFont(Theme::Font);
    logo.setString("HEXXAGON");
    logo.setPosition({ (window->getSize().x - logo.getGlobalBounds().width) / 2.f, yTop - 200 });
}
