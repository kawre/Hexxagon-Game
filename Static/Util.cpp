//
// Created by kawre on 21.05.2023.
//

#include "../Headers/Util.h"
#include <SFML/Graphics.hpp>
#include <cmath>

double Util::distance(sf::Vector2f a, sf::Vector2f b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double Util::distance(HexagonShape* hex1, HexagonShape* hex2)
{
    return distance(hex1->getPosition(), hex2->getPosition());
}

float Util::height(float a)
{
    return sqrtf(3) * a * 1 / 2;
}