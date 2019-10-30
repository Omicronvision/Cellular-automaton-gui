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
            file >> outputGrid[i][j];
        }
    }
    //window frame rate limit
    window.setFramerateLimit(60);
    //Cells
    alive.setColor(sf::Color::Yellow); alive.setSize(10, 10);
    //alive.setOutThickness(1); alive.setOutColor(sf::Color::Blue);
    dead.setColor(sf::Color::Black); dead.setSize(10, 10);
    //dead.setOutThickness(1); dead.setOutColor(sf::Color::Blue);
    cell2.setColor(sf::Color::Green); cell2.setSize(10, 10);
    //cell2.setOutThickness(1); cell2.setOutColor(sf::Color::Blue);
    cell3.setColor(sf::Color::Red); cell3.setSize(10, 10);
    //cell3.setOutThickness(1); cell3.setOutColor(sf::Color::Blue);
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
            } else if(outputGrid[i][j] == '.')
            {

            } else if(outputGrid[i][j] == 'x')
            {
                cell2.setPosition(j * 10, i * 10);
                cell2.draw(window);
            } else if(outputGrid[i][j] == 'z')
            {
                cell3.setPosition(j * 10, i * 10);
                cell3.draw(window);
            }
        }
    }
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
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
            /*
            . -> Empty
            O -> Robot
            x -> Construction
            */
            int neighbours = 0;
            int constructions = 0;
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


            if(numberGrid[i][j] != 0)
                numberGrid[i][j]--;
            if(copiedGrid[i][j] == 'x' && numberGrid[i][j] == 0)
                outputGrid[i][j] = 'O';

            if(neighbours == 1 && copiedGrid[i][j] == 'O')
            {
                outputGrid[i][j] = '.';
                outputGrid[i][j+1] = 'O';
            } else if(neighbours == 2 && copiedGrid[i][j] == 'O')
            {
                outputGrid[i][j] = '.';
                outputGrid[i][j-1] = 'O';
            } else if(neighbours == 3 && copiedGrid[i][j] == '.')
            {
                outputGrid[i][j] = 'x';
                numberGrid[i][j] = 3;
            } else if(neighbours >= 4 && copiedGrid[i][j] == 'O')
            {
                outputGrid[i][j] = '.';
            } else if(neighbours >= 3 && copiedGrid[i][j] == 'x')
            {
                outputGrid[i][j] = '.';
            }
        }
    }
}
