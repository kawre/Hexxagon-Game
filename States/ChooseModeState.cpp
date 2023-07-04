//
// Created by kawre on 25.05.2023.
//

#include "../Headers/ChooseModeState.h"
#include "../Static/Theme.h"
#include "../Headers/GamePlayState.h"

ChooseModeState::ChooseModeState(sf::RenderWindow* window, StateStack& state)
    : against(Against::COMPUTER),
      window(window),
      state(state)
{
    initButton();
    initRadioButtons();
}

void ChooseModeState::handleEvents(sf::Event& e)
{
    button.handleInput(window, e);

    for (auto& rBtn : radioButtons)
        rBtn.handleInput(window, e);
}

void ChooseModeState::update()
{
    float radioGap = 10;
    float buttonGap = 30;
    auto winSize = window->getSize();

    auto radioBtnRect = radioButton.getGlobalBounds();
    auto btnRect = button.getGlobalBounds();
    float totalHeight = radioBtnRect.height * 2 + radioGap + buttonGap + btnRect.height;
    float yTop = (winSize.y - totalHeight) / 2.f;

    button.setPosition({ winSize.x / 2.f, (winSize.y + totalHeight - btnRect.height) / 2.f });
    for (int i = 0; i < radioButtons.size(); i++)
    {
        auto& radio = radioButtons.at(i);
        radio.setPosition({ button.getGlobalBounds().left, yTop + (radioBtnRect.height + radioGap) * i });
    }
}

void ChooseModeState::render()
{
    window->clear(Theme::Background);

    for (auto& radio : radioButtons)
        radio.drawTo(window);
    button.drawTo(window);

    window->display();
}

void ChooseModeState::initButton()
{
    button.setFont(Theme::Font);
    button.setTextSize(40);
    button.setText("START GAME");
    button.setPadding({ 90, 15 });

    button.addCallback(sf::Event::MouseButtonPressed, sf::Mouse::Left,
        [&]() {
            state.pushState(std::make_unique<GamePlayState>(window, state, against));
        });
}

void ChooseModeState::initRadioButtons()
{
    radioButton.setFont(Theme::Font);

    // VS Computer
    radioButton.clearCallbacks();
    radioButton.setText("PLAYER VS COMPUTER");
    radioButton.setSelected(true);
    radioButton.addCallback(sf::Event::MouseButtonPressed, sf::Mouse::Left, [&]() {
        deFocusRadioButtons();
        against = Against::COMPUTER;
    });
    radioButtons.push_back(radioButton);

    // VS Player
    radioButton.clearCallbacks();
    radioButton.setText("PLAYER VS PLAYER");
    radioButton.setSelected(false);
    radioButton.addCallback(sf::Event::MouseButtonPressed, sf::Mouse::Left, [&]() {
        deFocusRadioButtons();
        against = Against::PLAYER;
    });
    radioButtons.push_back(radioButton);
}

void ChooseModeState::deFocusRadioButtons()
{
    for (auto& rBtn : radioButtons)
        rBtn.setSelected(false);
}
