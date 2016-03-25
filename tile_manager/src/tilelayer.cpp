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

#include "tile_manager/tilelayer.h"

#include <iostream>

bool TileLayer::load(const Tmx::TileLayer& tileLayer,
                     std::vector<TileSet>& tileSets,
                     int width, int height) {

  auto& props = tileLayer.GetProperties();
  animated = props.GetIntProperty("animated",0) == 1;

  // populate the vertex array, with one quad per tile
  for (unsigned int x = 0; x < width; ++x) {
    for (unsigned int y = 0; y < height; ++y) {
      int tilesetIndex = tileLayer.GetTileTilesetIndex(x, y);
      if (tilesetIndex == -1 || tilesetIndex > tileSets.size()) {
        //skip
      } else {
        int tileNumber = tileLayer.GetTileId(x, y);

        TileSet& tileset = tileSets[tilesetIndex];
        auto it = m_fragments.find(tilesetIndex);
        if (it == m_fragments.end()) {
          auto pair = m_fragments.insert(
              std::make_pair(tilesetIndex, LayerFragment(tileset, animated)));
          it = pair.first;
        }
        LayerFragment& frag = it->second;

        frag.add(tileset.getQuad(x, y, tileNumber));
      }
    }
  }
  return true;
}


void TileLayer::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  for (auto& it: m_fragments) {
    const LayerFragment& frag  = it.second;

    target.draw(frag, states);
  }
}
