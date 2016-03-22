#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "tilemap.h"

constexpr float anim_period = 0.3;

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

    sf::Clock anim_clock;
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
                break;
            }
        }
        sf::Time elapsed = anim_clock.getElapsedTime();
        if (elapsed.asSeconds() >= anim_period) {
          anim_clock.restart();
          map.next_frame();
        }

        // draw the map
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
