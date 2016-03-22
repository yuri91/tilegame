#include <SFML/Window.hpp>

#include <iostream>

#include "tilemap.h"

int main(int argc, char* argv[])
{
    // create the tilemap from the level definition
    TileMap map;
    if (!map.load(argv[1]))
        return -1;

    sf::Vector2u mapSize = map.getMapSize();
    sf::Vector2u tileSize = map.getTileSize();
    // create the window
    sf::RenderWindow window(sf::VideoMode(mapSize.x*tileSize.x, mapSize.y*tileSize.y), "Tilemap");
    window.setVerticalSyncEnabled(true);

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
              case sf::Event::Closed:
                window.close();
                break;
              case sf::Event::KeyPressed:
                std::cout<<event.key.code<<std::endl;
                break;
            }
        }

        // draw the map
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
