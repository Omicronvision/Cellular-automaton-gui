#include "Cell.h"

void Cell::setSize(int x, int y)
{
    form.setSize(sf::Vector2f(x, y));
}

void Cell::setColor(sf::Color color)
{
    form.setFillColor(color);
}

void Cell::setOutThickness(int s)
{
    form.setOutlineThickness(s);
}

void Cell::setPosition(int x, int y)
{
    form.setPosition(x, y);
}

void Cell::draw(sf::RenderWindow &window)
{
    window.draw(form);
}

void Cell::setOutColor(sf::Color color)
{
    form.setOutlineColor(color);
}
