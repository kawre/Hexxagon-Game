//
// Created by kawre on 28.05.2023.
//

#ifndef _BESTSCORESSTATE_H_
#define _BESTSCORESSTATE_H_

#include "State.h"
#include "StateStack.h"
#include "Button.h"
#include "Score.h"
#include <vector>

class BestScoresState : public State
{
 private:
    sf::RenderWindow* window;
    StateStack& state;
    Button quitButton;

    Score score;
    std::vector<Score> scores;

 public:
    BestScoresState(sf::RenderWindow*, StateStack&);

    void initQuitButton();
    void loadScores();

    void handleEvents(sf::Event&) override;
    void update() override;
    void render() override;
};

#endif //_BESTSCORESSTATE_H_
