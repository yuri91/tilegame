#include "./tileset.h"

bool TileSet::load(const Tmx::Tileset& tileset) {

  m_tileSize = sf::Vector2u(tileset.GetTileWidth(), tileset.GetTileHeight());

    // load the tileset texture
    if (!m_texture.loadFromFile(tileset.GetImage()->GetSource()))
      return false;

    return true;
}

Quad TileSet::getQuad(int x, int y, int tileNumber) {
  // find its position in the tileset texture
  int tu = tileNumber % (m_texture.getSize().x / m_tileSize.x);
  int tv = tileNumber / (m_texture.getSize().x / m_tileSize.x);

  Quad quad;

  // define its 4 corners
  quad[0].position = sf::Vector2f(x * m_tileSize.x,
                                  y * m_tileSize.y);
  quad[1].position = sf::Vector2f((x + 1) * m_tileSize.x,
                                  y * m_tileSize.y);
  quad[2].position = sf::Vector2f((x + 1) * m_tileSize.x,
                                  (y + 1) * m_tileSize.y);
  quad[3].position = sf::Vector2f(x * m_tileSize.x,
                                  (y + 1) * m_tileSize.y);

  // define its 4 texture coordinates
  quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x,
                                   tv * m_tileSize.y);
  quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x,
                                   tv * m_tileSize.y);
  quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x,
                                   (tv + 1) * m_tileSize.y);
  quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x,
                                   (tv + 1) * m_tileSize.y);
  return quad;
}
