//
// Created by kawre on 21.05.2023.
//

#ifndef HEXXAGON_UTIL_H
#define HEXXAGON_UTIL_H

#include <SFML/Graphics.hpp>
#include "HexagonShape.h"

namespace Util
{
    /**
     * @brief oblicza dlugość odcinka między dwoma punktami
     * @param a,b punkty w układzie kartezjańskim
     * @return długość odcinka między dwoma punktami
     */
    double distance(sf::Vector2f a, sf::Vector2f b);
    double distance(HexagonShape* a, HexagonShape* b);

    /**
     * @brief oblicza wysokość trójkąta rownobocznego zawartego w hexagonie
     * @param a bok trójkąta
     * @return wysokość trójkąta rownobocznego
     */
    float height(float a);
};

#endif //HEXXAGON_UTIL_H