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

#include "tile_manager/tilemap.h"

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

  std::string basepath = map.GetFilepath();
  for (int i = 0; i < map.GetNumTilesets(); i++) {
    const Tmx::Tileset *tileset = map.GetTileset(i);
    m_tilesets.emplace_back();
    if (!m_tilesets.back().load(*tileset, basepath))
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
