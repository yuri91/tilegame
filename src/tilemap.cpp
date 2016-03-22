#include "./tilemap.h"

#include <iostream>


bool TileMap::load(const std::string& tmx_path) {

  Tmx::Map map;
  map.ParseFile(tmx_path);

  if (map.HasError()) {
    return false;
  }

  int width = map.GetWidth();
  int height = map.GetHeight();

  m_mapSize = sf::Vector2u(width, height);

  m_tileSize = sf::Vector2u(map.GetTileWidth(), map.GetTileHeight());

  for (int i = 0; i < map.GetNumTilesets(); i++) {
    const Tmx::Tileset *tileset = map.GetTileset(i);
    m_tilesets.emplace_back();
    if (!m_tilesets.back().load(*tileset))
      return false;
  }

  for (int j = 0; j < map.GetNumTileLayers(); j++) {
    const Tmx::TileLayer *tileLayer = map.GetTileLayer(j);
    m_tilelayers.emplace_back();
    if (!m_tilelayers.back().load(*tileLayer, m_tilesets, width, height))
      return false;
  }

  return true;
}

void TileMap::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  for (auto& tilelayer: m_tilelayers) {
    target.draw(tilelayer, states);
  }
}
