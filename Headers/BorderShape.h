//
// Created by kawre on 21.05.2023.
//

#ifndef HEXXAGON_BORDERSHAPE_H
#define HEXXAGON_BORDERSHAPE_H

#include <SFML/Graphics.hpp>

class BorderShape : public sf::CircleShape
{
public:
    BorderShape();

    /**
     * @brief ustala kolor ramki pokazującej możliwość wykononia ruchu
     *        w zależności od odleglości
     * @param dist odległość między dwoma hexagonami
     */
    void setColorByDist(double dist);
};


#endif //HEXXAGON_BORDERSHAPE_H
