//
// Created by kawre on 21.05.2023.
//


#include <SFML/Graphics.hpp>
#include "../Headers/PawnShape.h"
#include "../Static/Theme.h"

PawnShape::PawnShape() : sf::CircleShape((Theme::Hexagon::Radius - Theme::Hexagon::OutlineThickness) * 0.5f), team(None)
{
    this->setOrigin({ getRadius(), getRadius() });
}

Team PawnShape::getTeam() const
{
    return this->team;
}

void PawnShape::setTeam(Team team)
{
    this->team = team;
    this->setFillColor(getColor(this->team));
}

sf::Color PawnShape::getColor(Team team)
{
    return team == Team::White ? Theme::WhitePawn : Theme::RedPawn;
}

Team PawnShape::getTeam(int col, int row)
{
    int bh = Theme::BoardHeight;
    col = abs(col);

    if ((col == 0 && row == 0) ||
        (col == bh / 2 && (row == bh / 2)))
    { return White; }
    else if ((col == 0 && row == bh - 1) ||
             (col == bh / 2 && row == 0))
    { return Red; }
    else
    { return None; }
}