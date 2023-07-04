//
// Created by kawre on 24.05.2023.
//

#ifndef HEXXAGON_TEXTBOX_H
#define HEXXAGON_TEXTBOX_H

#include <SFML/Graphics.hpp>

class TextBox
{
 private:
    sf::Text text;

 public:
    TextBox(int, sf::Color);

    // Setters
    void setFont(const sf::Font&);
    void setPosition(sf::Vector2f);
    void setString(const sf::String&);

    // Getters
    sf::FloatRect getGlobalBounds() const;

    //
    void drawTo(sf::RenderWindow*);
};

#endif //HEXXAGON_TEXTBOX_H
