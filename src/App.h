#ifndef APP_H
#define APP_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "Cell.h"

#define WIDTH 1280
#define HEIGHT 720
#define XGRID 140
#define YGRID 80

class App
{
    public:
        App();
        void run();

    private:
        void processEvents();
        void update();
        void render();
        void compareGrids();
        void newGeneration();
        char outputGrid[YGRID][XGRID];
        char copiedGrid[YGRID][XGRID];
        int numberGrid[YGRID][XGRID];
        bool start = false;
        int direction = 1;
        std::ifstream file;
        sf::RenderWindow window;
        Cell alive, dead, cell2, cell3;
};

#endif // APP_H
