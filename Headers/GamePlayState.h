//
// Created by kawre on 23.05.2023.
//

#ifndef HEXXAGON_GAMEPLAYSTATE_H
#define HEXXAGON_GAMEPLAYSTATE_H

#include "State.h"
#include <stack>
#include "Board.h"
#include "StateStack.h"
#include "Button.h"
#include "ChooseModeState.h"

class GamePlayState : public State
{
 private:
    sf::RenderWindow* window;
    StateStack& state;
    sf::Clock clock;
    bool gameOver;

    // Game Objects
    Board board;
    Button quitButton;
    sf::Text whiteCount;
    sf::Text redCount;
    sf::Text gameStatus;
    sf::Text time;

 public:
    GamePlayState(sf::RenderWindow*, StateStack&, Against);
    GamePlayState(sf::RenderWindow*, StateStack&, Against, const sf::String& path);

    void initQuitButton();
    void initCountTexts();
    void initStatusText();
    void initTimeText();
    void saveToScores();

    void handleEvents(sf::Event& e) override;
    void update() override;
    void render() override;
};

#endif //HEXXAGON_GAMEPLAYSTATE_H
