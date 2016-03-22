#include "./tilelayer.h"

#include <iostream>

bool TileLayer::load(const Tmx::TileLayer& tileLayer,
                     std::vector<TileSet>& tileSets,
                     int width, int height) {

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
              std::make_pair(tilesetIndex, LayerFragment(tileset)));
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
