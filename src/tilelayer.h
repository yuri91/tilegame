#ifndef TILELAYER_H_
#define TILELAYER_H_

#include <SFML/Graphics.hpp>
#include <tmxparser/Tmx.h>

#include <vector>
#include <map>

#include "./layerfragment.h"

class TileLayer : public sf::Drawable, public sf::Transformable {
 public:
  bool load(const Tmx::TileLayer& tileLayer,
            std::vector<TileSet>& tileSets, int width, int height);

  void next_frame() {
    for (auto& it: m_fragments) {
      it.second.next_frame();
    }
  }

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  std::map<int, LayerFragment> m_fragments;

  bool animated{false};
};

#endif  // TILELAYER_H_
