//
// Created by kawre on 25.05.2023.
//

#ifndef _RADIOBUTTON_H_
#define _RADIOBUTTON_H_

#include "Button.h"

class RadioButton : public Button
{
 private:
    sf::CircleShape radio;
    bool selected;
    float gap;

 public:
    RadioButton();

    void handleInput(sf::RenderWindow* window, const sf::Event& event) override;
    void update() override;
    void drawTo(sf::RenderWindow* window) override;

    void setGap(float);
    void setSelected(bool);
    void setRadius(float);
};

#endif //_RADIOBUTTON_H_
