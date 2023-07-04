//
// Created by kawre on 21.05.2023.
//

#ifndef HEXXAGON_PAWNSHAPE_H
#define HEXXAGON_PAWNSHAPE_H

#include <SFML/Graphics.hpp>
#include "Team.h"

class PawnShape : public sf::CircleShape
{
public:
    Team team;

public:
    PawnShape();

    Team getTeam() const;
    void setTeam(Team team);

    // static
    static sf::Color getColor(Team team);
    static Team getTeam(int col, int row);
};


#endif //HEXXAGON_PAWNSHAPE_H
