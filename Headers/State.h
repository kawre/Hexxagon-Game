//
// Created by kawre on 23.05.2023.
//

#ifndef HEXXAGON_GAMESTATE_H
#define HEXXAGON_GAMESTATE_H

#include "SFML/Graphics.hpp"

class State
{
 public:
	virtual void handleEvents(sf::Event& e) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif //HEXXAGON_GAMESTATE_H
