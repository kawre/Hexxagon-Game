//
// Created by kawre on 24.05.2023.
//

#include "../Headers/TextBox.h"

TextBox::TextBox(int size, sf::Color color)
{
    text.setFillColor(color);
    text.setCharacterSize(size);
    text.setString("INIT");
}

void TextBox::setFont(const sf::Font& font)
{
    this->text.setFont(font);
}

void TextBox::setPosition(sf::Vector2f pos)
{
    text.setPosition(pos);
}

void TextBox::setString(const sf::String& str)
{
    text.setString(str);
}

void TextBox::drawTo(sf::RenderWindow* window)
{
    window->draw(text);
}

sf::FloatRect TextBox::getGlobalBounds() const
{
    return text.getGlobalBounds();
}
