//
// Created by kawre on 25.05.2023.
//

#include <iostream>
#include "../Headers/RadioButton.h"
#include "../Static/Theme.h"

RadioButton::RadioButton() : selected(false), gap(25)
{
    radio.setFillColor(Theme::Radio::Fill);
    radio.setOutlineColor(Theme::Radio::Outline);
    radio.setOutlineThickness(-Theme::Radio::OutlineThickness);
    text.setFillColor(Theme::Radio::TextColor);
    setPadding({ 10, 10 });

    this->setRadius(Theme::Radio::Radius);
    this->setTextSize(Theme::Radio::TextSize);
    this->setText("INIT");
    this->setGap(Theme::Radio::Radius);
}

void RadioButton::handleInput(sf::RenderWindow* window, const sf::Event& e)
{
    if (this->button.getGlobalBounds().contains(sf::Vector2f(e.mouseButton.x, e.mouseButton.y)))
        for (auto& callback : callbacks)
        {
            auto eventTypes = callback.first;
            if (e.type == eventTypes.first && e.mouseButton.button == eventTypes.second)
            {
                callback.second();
                this->setSelected(true);
            }
        }
}

void RadioButton::update()
{
    float r = radio.getRadius();
    radio.setPosition(position);
    auto radioRect = radio.getGlobalBounds();

    auto textRect = text.getLocalBounds();
    text.setOrigin({ 0, textRect.height / 2.f });
    text.setPosition({ radioRect.left - textRect.left + (r * 2.f) + gap,
                       radioRect.top - textRect.top + r });

    button.setOrigin(padding);
    button.setSize({ (2 * (r + padding.x)) + gap + textRect.width, 2 * (r + padding.y) });
    button.setPosition({ radioRect.left, radioRect.top });
}

void RadioButton::drawTo(sf::RenderWindow* window)
{
    radio.setFillColor(selected ? Theme::Radio::FillSelected : Theme::Radio::Fill);
    window->draw(radio);

    text.setFillColor(selected ? Theme::Radio::TextColorSelected : Theme::Radio::TextColor);
    window->draw(text);
}

void RadioButton::setGap(float gap)
{
    this->gap = gap;
    update();
}

void RadioButton::setSelected(bool sel)
{
    this->selected = sel;
}

void RadioButton::setRadius(float radius)
{
    this->radio.setRadius(radius);
}
