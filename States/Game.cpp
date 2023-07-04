//
// Created by kawre on 20.05.2023.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Headers/Game.h"
#include "../Static/Theme.h"
#include "../Headers/Util.h"
#include <cmath>

// Constructor / Destructor
Game::Game() : window(nullptr)
{
    this->init();
}

Game::~Game()
{
    delete this->window;
}

// Init
void Game::init()
{
    std::string title = "Hexxagon";

    float bh = Theme::BoardHeight;
    float r = Theme::Hexagon::Radius;
    float h = Theme::Hexagon::Height;
    float gap = Theme::Hexagon::Gap;

    unsigned int height = (h * 2) * bh + (gap * 2 * (bh - 1));
    unsigned int width = r * 2 * ceilf(bh / 2.f) + r * (bh / 2) + (Util::height(gap * 2) * (bh - 1));

    int xPadding = r * 2;
    int yPadding = h * 2;

    this->videoMode = sf::VideoMode({ width + 2 * xPadding, height + 2 * yPadding });
    sf::ContextSettings contextSettings(0, 0, 8);
    auto styles = sf::Style::Titlebar | sf::Style::Close;

    this->window = new sf::RenderWindow(videoMode, title, styles, contextSettings);
    this->window->setFramerateLimit(165);

    this->state.pushState(std::make_unique<MenuState>(window, state));
}

// Accessors
bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    sf::Event e{};

    while (window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            window->close();

        state.handleEvents(e);
    }
}

void Game::update()
{
    state.update();
}

void Game::render()
{
    state.render();
}