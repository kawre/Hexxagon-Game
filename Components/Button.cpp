//
// Created by kawre on 24.05.2023.
//

#include "../Headers/Button.h"
#include "../Static/Theme.h"

Button::Button()
{
    button.setFillColor(Theme::Button::Background);
    text.setFillColor(Theme::Button::TextColor);
}

void Button::setFont(const sf::Font& font)
{
    this->text.setFont(font);
}

void Button::setText(const sf::String& str)
{
    text.setString(str);
    update();
}

void Button::drawTo(sf::RenderWindow* window)
{
    window->draw(button);
    window->draw(text);
}

void Button::setPosition(sf::Vector2f pos)
{
    position = pos;
    update();
}

void Button::setTextSize(int size)
{
    text.setCharacterSize(size);
    update();
}

void Button::update()
{
    auto textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2.f, textRect.height / 2.f);

    float btnWidth = padding.x * 2 + textRect.width;
    float btnHeight = padding.y * 2 + textRect.height;
    button.setSize({ btnWidth, btnHeight });
    button.setOrigin(button.getSize() / 2.f);

    button.setPosition(position);
    auto btnPos = button.getPosition();
    text.setPosition({ btnPos.x - textRect.left, btnPos.y - textRect.top });
}

void Button::setPadding(sf::Vector2f padding)
{
    this->padding = padding;
    update();
}

sf::Vector2f Button::getSize() const
{
    return button.getSize();
}

void Button::handleInput(sf::RenderWindow* window, const sf::Event& e)
{
    if (this->button.getGlobalBounds().contains(sf::Vector2f(e.mouseButton.x, e.mouseButton.y)))
        for (const auto& callback : callbacks)
        {
            auto eventTypes = callback.first;
            if (e.type == eventTypes.first && e.mouseButton.button == eventTypes.second)
                callback.second();
        }
}

void Button::addCallback(sf::Event::EventType eventType, sf::Mouse::Button mouseButton,
    const std::function<void()>& callback)
{
    auto eventPair = std::pair(eventType, mouseButton);
    callbacks.emplace_back(eventPair, callback);
}

sf::Rect<float> Button::getGlobalBounds() const
{
    return button.getGlobalBounds();
}

void Button::clearCallbacks()
{
    this->callbacks.clear();
}
