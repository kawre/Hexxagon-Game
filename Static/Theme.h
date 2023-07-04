//
// Created by kawre on 21.05.2023.
//

#ifndef HEXXAGON_THEME_H
#define HEXXAGON_THEME_H

#include <cmath>
#include "SFML/Graphics.hpp"

class Theme
{
 public:
    // Background
    inline static const sf::Color Background = sf::Color(0x181818FF);
    inline static sf::Font Font;

    // Pawn
    inline static const sf::Color RedPawn = sf::Color(0xFF0303FF);
    inline static const sf::Color WhitePawn = sf::Color(0xF0EEEDFF);

    // Dimensions
    inline static const int BoardHeight = 9;

    // Button Theme
    class Button
    {
     public:
        inline static const sf::Color Background = sf::Color(0x404258FF);
        inline static const sf::Color TextColor = sf::Color::White;
    };

    // Border Theme
    class Border
    {
     public:
        inline static const sf::Color Fill = sf::Color::Transparent;
        inline static const sf::Color OutlineClose = sf::Color(0x16FF00FF);
        inline static const sf::Color OutlineFar = sf::Color(0xFFE61BFF);
    };

    // Hexagon Theme
    class Hexagon
    {
     public:
        inline static const sf::Color Fill = sf::Color(0x0A2647FF);
        inline static const sf::Color Outline = sf::Color(0x205295FF);

        inline static const float Radius = 40;
        inline static const float OutlineThickness = 5;
        inline static const float Gap = 5;
        inline static const float Height = (sqrtf(3) * Radius) / 2.f;
    };

    // Radio Button Theme
    class Radio
    {
     public:
        inline static const sf::Color Fill = sf::Color::Transparent;
        inline static const sf::Color FillSelected = Theme::Hexagon::Outline;

        inline static const sf::Color TextColor = sf::Color(255, 255, 255, 60);
        inline static const sf::Color TextColorSelected = sf::Color::White;

        inline static const sf::Color Outline = Theme::Hexagon::Outline;

        inline static const float Radius = 18;
        inline static const float OutlineThickness = 4;
        inline static const float TextSize = 32;
    };
};

#endif //HEXXAGON_THEME_H
