//
// Created by kawre on 20.05.2023.
//

#ifndef HEXXAGON_GAME_H
#define HEXXAGON_GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "HexagonShape.h"
#include "PawnShape.h"
#include "Team.h"
#include "Board.h"
#include "State.h"
#include "MenuState.h"
#include "State.h"
#include "StateStack.h"

#include <vector>
#include <stack>

class Game
{
 private:
	// Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Font font;
	StateStack state;

	// Init
	void init();

 public:
	// Constructor / Destructor
	Game();
	~Game();

	// Accessors
	bool running() const;

	void pollEvents();
	void update();
	void render();
};

#endif //HEXXAGON_GAME_H
