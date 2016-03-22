#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "tilemap.h"

constexpr float anim_period = 0.3;
constexpr float zoom_factor = 1.1;

int main(int argc, char* argv[])
{
    // create the tilemap from the level definition
    TileMap map;
    if (!map.load(argv[1]))
        return -1;

    sf::Vector2u mapSize = map.getMapSize();
    sf::Vector2u tileSize = map.getTileSize();
    // create the window

    sf::Vector2u windowSize = sf::Vector2u(mapSize.x * tileSize.x,
                                           mapSize.y * tileSize.y);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y),
                            "Tilemap");
    window.setVerticalSyncEnabled(true);

    sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    float scale = 1;
    sf::Vector2i prevPos;
    bool dragging = false;

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
              case sf::Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                  int delta = event.mouseWheelScroll.delta;
                  float zoom;
                  if (delta < 0) {
                    zoom = zoom_factor;
                  } else{
                    zoom = 1.0/zoom_factor;
                  }
                  sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                  sf::Vector2f worldPosPrev = window.mapPixelToCoords(pixelPos);
                  view.zoom(zoom);
                  window.setView(view);
                  sf::Vector2f worldPosCurr = window.mapPixelToCoords(pixelPos);
                  sf::Vector2f move = worldPosPrev-worldPosCurr;
                  view.move(move.x, move.y);
                  scale *= zoom;
                }
                break;
              case sf::Event::Resized:
                view.setSize(event.size.width, event.size.height);
                view.zoom(scale);
                break;

              case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                  prevPos = sf::Vector2i(event.mouseButton.x,
                                          event.mouseButton.y);
                  dragging = true;
                }
                break;
              case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                  dragging = false;
                }
                break;
            }
        }
        sf::Time elapsed = anim_clock.getElapsedTime();
        if (elapsed.asSeconds() >= anim_period) {
          anim_clock.restart();
          map.next_frame();
        }
        if (dragging) {
          sf::Vector2i curPos = sf::Mouse::getPosition(window);

          int dx = prevPos.x - curPos.x;
          int dy = prevPos.y - curPos.y;

          prevPos = curPos;

          view.move(dx*scale, dy*scale);
        }

        // draw the map
        window.clear();
        window.setView(view);
        window.draw(map);
        window.display();
    }

    return 0;
}
