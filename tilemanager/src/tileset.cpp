//  ISC License
//
//  Copyright (c) 2016, Yuri Iozzelli <y.iozzelli@gmail.com>
//
//  Permission to use, copy, modify, and/or distribute this software for any
//  purpose with or without fee is hereby granted, provided that the above
//  copyright notice and this permission notice appear in all copies.
//
//  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
//  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
//  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
//  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
//  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
//  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
//  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#include "tilemanager/tileset.h"

#include <iostream>

namespace Tm {

bool TileSet::load(const Tmx::Tileset& tileset, std::string basepath) {

  m_tileSize = sf::Vector2u(tileset.GetTileWidth(), tileset.GetTileHeight());

  std::string source = basepath + "/" + tileset.GetImage()->GetSource();

  m_textures.emplace_back();
  // load the tileset texture
  if (!m_textures.back().loadFromFile(source))
    return false;

  m_textureSize = m_textures.back().getSize();

  // TODO: this is super ugly
  std::string suffix = "0.png";
  if (std::equal(suffix.rbegin(), suffix.rend(), source.rbegin())) {
    *(source.rbegin()+4) = '1';
    m_textures.emplace_back();
    if (!m_textures.back().loadFromFile(source))
      return false;
  }

  return true;
}

Quad TileSet::getQuad(int x, int y, int tileNumber) {
  // find its position in the tileset texture
  int tu = tileNumber % (m_textureSize.x / m_tileSize.x);
  int tv = tileNumber / (m_textureSize.x / m_tileSize.x);

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

}  // namespace Tm
