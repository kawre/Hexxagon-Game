//
// Created by kawre on 20.05.2023.
//

#include "../Headers/Game.h"
#include <vector>
#include "../Static/Theme.h"
#include "../Headers/Util.h"
#include "../Headers/HexagonShape.h"

HexagonShape::HexagonShape() : hexagon(Theme::Hexagon::Radius, 6), pawn(), focused(false)
{
    // Background
    hexagon.setFillColor(Theme::Hexagon::Fill);

    // OutlineThickness
    hexagon.setOutlineColor(Theme::Hexagon::Outline);
    hexagon.setOutlineThickness(-Theme::Hexagon::OutlineThickness);

    // Origin
    hexagon.setOrigin({ Theme::Hexagon::Radius, Theme::Hexagon::Radius });

    // Rotate
    hexagon.setRotation(90);
}

std::vector<HexagonShape*>
HexagonShape::findNearby(float range, std::unordered_map<std::string, HexagonShape>& hexagons) const
{
    std::vector<HexagonShape*> vec;
    sf::Vector2f pos = this->getPosition();

    float h = Theme::Hexagon::Height + Theme::Hexagon::Gap / 2.f;
    for (auto& [grid, hex] : hexagons)
    {
        double dist = Util::distance(hex.getPosition(), pos);
        if (dist <= h * range && &hex != this) vec.push_back(&hex);
    }

    return vec;
}

bool HexagonShape::containsPawn() const
{
    return this->pawn.getTeam() != Team::None;
}

bool HexagonShape::isFocused() const
{
    return focused;
}

void HexagonShape::setFocused(bool b)
{
    this->focused = b;
}

void HexagonShape::drawTo(sf::RenderWindow* window)
{
    window->draw(hexagon);
    if (this->containsPawn()) window->draw(this->pawn);
    if (this->isFocused()) window->draw(this->border);
}

sf::Vector2f HexagonShape::getPosition() const
{
    return position;
}

sf::FloatRect HexagonShape::getGlobalBounds() const
{
    return hexagon.getGlobalBounds();
}

void HexagonShape::setPosition(sf::Vector2f pos)
{
    this->position = pos;
    update();
}

void HexagonShape::setGridPosition(int col, int row)
{
    gridPosition.first = col;
    gridPosition.second = row;
}

std::string HexagonShape::getGridPositionStr() const
{
    return std::to_string(gridPosition.first) + "," + std::to_string(gridPosition.second);
}

void HexagonShape::update()
{
    hexagon.setPosition(position);
    pawn.setPosition(position);
    border.setPosition(position);
}

void HexagonShape::setPawnTeam(Team team)
{
    this->pawn.setTeam(team);
}

Team HexagonShape::getPawnTeam() const
{
    return pawn.getTeam();
}