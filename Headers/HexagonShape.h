//
// Created by kawre on 20.05.2023.
//

#ifndef HEXXAGON_HEXAGONSHAPE_H
#define HEXXAGON_HEXAGONSHAPE_H

#include "SFML/Graphics.hpp"
#include "PawnShape.h"
#include "BorderShape.h"
#include <vector>

class HexagonShape
{
 public:
    bool focused;
    std::pair<int, int> gridPosition;
    sf::CircleShape hexagon;
    sf::Vector2f position;
    PawnShape pawn;
    BorderShape border;

 public:
    HexagonShape();

    /**
     * @brief znajduje wszystkie pobliskie hexagony względem podanych parametrów
     * @param range dozwolona odległość miedzy dwoma hexagnowami (range * (wysokość trójkąta równobocznego zawartego w hexagonie))
     * @param hexagons plansza gry
     * @return vector wskaźników wszystkich znalezionych hexagonów
     */
    std::vector<HexagonShape*> findNearby(float range, std::unordered_map<std::string, HexagonShape>& hexagons) const;

    void drawTo(sf::RenderWindow* window);
    void update();

    // setters
    void setPosition(sf::Vector2f vector2);
    void setGridPosition(int, int);
    void setPawnTeam(Team);
    void setFocused(bool);

    // getters
    bool containsPawn() const;
    bool isFocused() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    Team getPawnTeam() const;
    std::string getGridPositionStr() const;
};

#endif //HEXXAGON_HEXAGONSHAPE_H
