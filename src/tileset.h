#ifndef TILESET_H_
#define TILESET_H_

#include <SFML/Graphics.hpp>
#include <tmxparser/Tmx.h>

#include <vector>

typedef std::array<sf::Vertex, 4> Quad;

class TileSet {
 public:
  bool load(const Tmx::Tileset& tileset, std::string basepath);

  sf::Vector2u getTileSize() {
    return m_tileSize;
  }
  sf::Texture& getTexture(int i) {
    if (i >= m_textures.size())
      i = 0;
    return m_textures[i];
  }

  Quad getQuad(int x, int y, int tileNumber);

 private:
  std::vector<sf::Texture> m_textures;

  sf::Vector2u m_tileSize;
  sf::Vector2u m_textureSize;
};

#endif  // TILESET_H_
