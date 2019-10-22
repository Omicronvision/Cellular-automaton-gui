#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell
{
    public:
        void setSize(int x, int y);
        void setColor(sf::Color color);
        void setOutColor(sf::Color color);
        void setOutThickness(int s);
        void setPosition(int x, int y);
        void draw(sf::RenderWindow &window);

    private:
        sf::RectangleShape form;
};

#endif // CELL_H
