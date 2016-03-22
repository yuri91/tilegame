#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <SFML/Graphics.hpp>
#include <tmxparser/Tmx.h>

#include <vector>

#include "./tileset.h"
#include "./tilelayer.h"

class TileMap : public sf::Drawable, public sf::Transformable {
 public:
  bool load(const std::string& tmx_path);

  sf::Vector2u getMapSize() {
    return m_mapSize;
  }

  sf::Vector2u getTileSize() {
    return m_tileSize;
  }

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  std::vector<TileSet> m_tilesets;
  std::vector<TileLayer> m_tilelayers;

  sf::Vector2u m_mapSize;
  sf::Vector2u m_tileSize;
};

#endif  // TILEMAP_H_
