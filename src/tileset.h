#ifndef TILESET_H_
#define TILESET_H_

#include <SFML/Graphics.hpp>
#include <tmxparser/Tmx.h>

#include <vector>

typedef std::array<sf::Vertex, 4> Quad;

class TileSet {
 public:
  bool load(const Tmx::Tileset& tileset);

  sf::Vector2u getTileSize() {
    return m_tileSize;
  }
  sf::Texture& getTexture() {
    return m_texture;
  }

  Quad getQuad(int x, int y, int tileNumber);

 private:
  sf::Texture m_texture;
  sf::Vector2u m_tileSize;
};

#endif  // TILESET_H_
