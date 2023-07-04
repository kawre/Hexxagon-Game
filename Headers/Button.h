//
// Created by kawre on 24.05.2023.
//

#ifndef HEXXAGON_MAINMENUBUTTON_H
#define HEXXAGON_MAINMENUBUTTON_H

#include <SFML/Graphics.hpp>
#include "TextBox.h"
#include "State.h"

class Button
{
 protected:
    std::vector<std::pair<std::pair<sf::Event::EventType, sf::Mouse::Button>, std::function<void()>>> callbacks;
    sf::RectangleShape button;
    sf::Vector2f position;
    sf::Vector2f padding;
    sf::Text text;

 public:
    Button();

    /**
     * @brief przypisuje pewną funkcjonalność, która jest wykonywana w momencie spełnienia warunków z dwóch pierwszych parametrów
     * @param eventType określony typ eventu
     * @param mouseButton określony przycisk na myszce
     * @param function funkcja, która wywoła się w momencie spełnienia dwóch poprzednich warunków
     */
    void addCallback(sf::Event::EventType eventType, sf::Mouse::Button mouseButton,
        const std::function<void()>& function);
    void clearCallbacks();

    //
    virtual void handleInput(sf::RenderWindow*, const sf::Event&);
    virtual void update();
    virtual void drawTo(sf::RenderWindow* window);

    // Setters
    void setFont(const sf::Font&);
    void setText(const sf::String&);
    void setPosition(sf::Vector2f);
    void setTextSize(int size);
    void setPadding(sf::Vector2f);

    // Getters
    sf::Rect<float> getGlobalBounds() const;
    sf::Vector2f getSize() const;
};

#endif //HEXXAGON_MAINMENUBUTTON_H
