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

#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <SFML/Graphics.hpp>
#include <tmxparser/Tmx.h>

#include <vector>

#include "tilemanager/tileset.h"
#include "tilemanager/tilelayer.h"

namespace Tm {

class TileMap : public sf::Drawable, public sf::Transformable {
 public:
  bool load(const std::string& tmx_path);

  sf::Vector2u getMapSize() {
    return m_mapSize;
  }

  sf::Vector2u getTileSize() {
    return m_tileSize;
  }

  void next_frame() {
    for (auto& tilelayer: m_tilelayers) {
      tilelayer.next_frame();
    }
  }

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  std::vector<TileSet> m_tilesets;
  std::vector<TileLayer> m_tilelayers;

  sf::Vector2u m_mapSize;
  sf::Vector2u m_tileSize;
};

}  // namespace Tm

#endif  // TILEMAP_H_
