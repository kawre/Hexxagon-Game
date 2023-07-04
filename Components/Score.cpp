//
// Created by kawre on 02.06.2023.
//
#include "../Headers/Score.h"
#include "../Static/Theme.h"

Score::Score()
    : yourCount("0", Theme::Font, 24), enemyCount("0", Theme::Font, 24),
      gameLength("0:00", Theme::Font, 24), team("RED TEAM", Theme::Font, 24)
{
    bg.setOutlineColor(Theme::Button::Background);
    bg.setOutlineThickness(-5);
    bg.setFillColor(sf::Color::Transparent);
}

void Score::setTeam(Team team)
{
    this->team.setString(team == Team::Red ? "RED" : "WHITE");
}

void Score::setMovesCount(sf::Vector2i moves)
{
    yourCount.setString(std::to_string(moves.x));
    enemyCount.setString(std::to_string(moves.y));

    this->moves = moves;
}

void Score::setTime(std::string time)
{
    this->length = time;
    gameLength.setString(time);
}

void Score::drawTo(sf::RenderWindow* window)
{
    window->draw(bg);
    window->draw(enemyCount);
    window->draw(yourCount);
    window->draw(gameLength);
    window->draw(team);
}

sf::Vector2i Score::getMovesCount() const
{
    return moves;
}

void Score::setPosition(sf::Vector2f pos)
{
    position = pos;
    update();
}

void Score::update()
{
    bg.setPosition(position);
    auto bgRect = bg.getGlobalBounds();
    float y = bgRect.top + 20;

    team.setPosition({ bgRect.left + 40, y });
    yourCount.setPosition({ bgRect.left + 300, y });
    enemyCount.setPosition({ bgRect.left + 400, y });
    gameLength.setPosition({ bgRect.left + bgRect.width - 40 - gameLength.getGlobalBounds().width, y });
}

void Score::setSize(sf::Vector2f size)
{
    bg.setSize(size);
}
