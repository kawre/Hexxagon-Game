//
// Created by kawre on 28.05.2023.
//

#ifndef _SCORE_H_
#define _SCORE_H_

#include <SFML/Graphics.hpp>
#include "Team.h"

class Score
{
 private:
    sf::Vector2i moves;
    std::string length;
    std::string date;
    sf::Vector2f position;

    // objects
    sf::Text team;
    sf::Text yourCount;
    sf::Text enemyCount;
    sf::Text gameLength;
    sf::RectangleShape bg;

 public:
    Score();

    void setTeam(Team team);
    void setMovesCount(sf::Vector2i moves);
    void setTime(std::string time);
    void setPosition(sf::Vector2f);

    void drawTo(sf::RenderWindow*);
    void update();

    sf::Vector2i getMovesCount() const;
    void setSize(sf::Vector2f size);
};

#endif //_SCORE_H_
