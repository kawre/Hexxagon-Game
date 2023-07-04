//
// Created by kawre on 02.06.2023.
//

#include "../Headers/LoadGameState.h"
#include "../Static/Theme.h"
#include "../Headers/GamePlayState.h"

LoadGameState::LoadGameState(sf::RenderWindow* window, StateStack& state)
    : window(window), state(state)
{
    initQuitButton();
    initInputText();
    initLoadButton();
}

void LoadGameState::handleEvents(sf::Event& e)
{
    quitButton.handleInput(window, e);
    loadButton.handleInput(window, e);

    if (e.type == sf::Event::TextEntered)
    {
        if (e.text.unicode == '\b')
        {
            if (input.getSize() > 0)
            {
                input.erase(input.getSize() - 1);
                text.setString(input);
            }
        }
        else if (e.text.unicode < 128)
        {
            input += e.text.unicode;
            text.setString(input);
        }
    }
}

void LoadGameState::update()
{

}

void LoadGameState::render()
{
    window->clear(Theme::Background);

    quitButton.drawTo(window);

    window->draw(textBg);
    window->draw(text);
    loadButton.drawTo(window);

    window->display();
}

void LoadGameState::initQuitButton()
{
    auto winSize = window->getSize();

    quitButton.setFont(Theme::Font);
    quitButton.setTextSize(24);
    quitButton.setText("QUIT");

    float padding = 15;
    quitButton.setPadding({ padding, padding * 0.75f });

    auto qbtnRect = quitButton.getGlobalBounds();
    float margin = Theme::Hexagon::Radius;
    quitButton.setPosition({ qbtnRect.width / 2.f + margin, winSize.y - qbtnRect.height / 2.f - margin });

    quitButton.addCallback(sf::Event::MouseButtonPressed, sf::Mouse::Left,
        [this]() {
            state.menuState();
        });
}

void LoadGameState::initInputText()
{
    text.setFont(Theme::Font);
    textBg.setPosition(0, 200);
    textBg.setSize(sf::Vector2f(window->getSize().x, 50));
    textBg.setFillColor(Theme::Button::Background);
    text.setPosition(0, 205);
}

void LoadGameState::initLoadButton()
{
    loadButton.setFont(Theme::Font);
    loadButton.setText("LOAD");
    loadButton.setPadding({ 30, 15 });
    loadButton.setPosition({ window->getSize().x / 2.f, 300 });
    loadButton.addCallback(sf::Event::MouseButtonPressed, sf::Mouse::Left, [this]() {
        state.pushState(std::make_unique<GamePlayState>(window, state, Against::COMPUTER, input));
    });
}

