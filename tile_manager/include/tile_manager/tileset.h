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

#ifndef TILESET_H_
#define TILESET_H_

#include <SFML/Graphics.hpp>
#include <tmxparser/Tmx.h>

#include <vector>

namespace Tm {

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

}  // namespace Tm

#endif  // TILESET_H_
