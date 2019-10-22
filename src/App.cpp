#include "App.h"
#include "Cell.h"

App::App() : window(sf::VideoMode(WIDTH, HEIGHT), "Cellular automaton")
{
    srand(time(NULL));
    //save file into an array
    file.open("grid.txt");
    for(int i = 0; i < YGRID; i++)
    {
        for(int j = 0; j < XGRID; j++)
        {
            int r = rand() % 2;
            if(r == 0)
                outputGrid[i][j] = '.';
            else
                outputGrid[i][j] = 'O';
        }
    }
    //window frame rate limit
    window.setFramerateLimit(60);
    //Cells
    alive.setColor(sf::Color::White); alive.setSize(10, 10);
    alive.setOutThickness(1); alive.setOutColor(sf::Color::Blue);
    dead.setColor(sf::Color::Black); dead.setSize(10, 10);
    dead.setOutThickness(1); dead.setOutColor(sf::Color::Blue);
}

void App::run()
{
    while(window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void App::processEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                window.close();
            }
        }
    }
}

void App::update()
{
    newGeneration();
}

void App::render()
{
    window.clear(sf::Color::Black);
    for(int i = 0; i < YGRID; i++)
    {
        for(int j = 0; j < XGRID; j++)
        {
            if(outputGrid[i][j] == 'O')
            {
                alive.setPosition(j * 10, i * 10);
                alive.draw(window);
            } else
            {
                dead.setPosition(j * 10, i * 10);
                dead.draw(window);
            }
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    window.display();
}

void App::compareGrids()
{
    for(int i = 0; i < YGRID; i++)
    {
        for(int j = 0; j < XGRID; j++)
        {
            copiedGrid[i][j] = outputGrid[i][j];
        }
    }
}

void App::newGeneration()
{
    compareGrids();
    for(int i = 0; i < YGRID; i++)
    {
        for(int j = 0; j < XGRID; j++)
        {
            int neighbours = 0;
            if(copiedGrid[i-1][j-1] == 'O')
                neighbours++;
            if(copiedGrid[i-1][j] == 'O')
                neighbours++;
            if(copiedGrid[i-1][j+1] == 'O')
                neighbours++;
            if(copiedGrid[i][j-1] == 'O')
                neighbours++;
            if(copiedGrid[i][j+1] == 'O')
                neighbours++;
            if(copiedGrid[i+1][j-1] == 'O')
                neighbours++;
            if(copiedGrid[i+1][j] == 'O')
                neighbours++;
            if(copiedGrid[i+1][j+1] == 'O')
                neighbours++;

            if(neighbours < 2)
                outputGrid[i][j] = '.';
            else if(neighbours == 3)
                outputGrid[i][j] = 'O';
            else if(neighbours > 3)
                outputGrid[i][j] = '.';
        }
    }
}
