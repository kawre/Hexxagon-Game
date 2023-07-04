//
// Created by kawre on 21.05.2023.
//

#include "../Headers/BorderShape.h"
#include "../Static/Theme.h"

BorderShape::BorderShape()
	: sf::CircleShape(Theme::Hexagon::Radius - Theme::Hexagon::OutlineThickness, 6)
{
	this->setFillColor(Theme::Border::Fill);
	this->setOutlineThickness(Theme::Hexagon::OutlineThickness * .5f);
	this->setOrigin({ this->getRadius(), this->getRadius() });
	this->setRotation(90);
}

void BorderShape::setColorByDist(double dist)
{
	float h = Theme::Hexagon::Height + Theme::Hexagon::Gap / 2.f;
	auto outline = (dist >= h && dist <= h * 3) ? Theme::Border::OutlineClose : Theme::Border::OutlineFar;
	this->setOutlineColor(outline);
}
