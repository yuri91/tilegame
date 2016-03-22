#ifndef LAYERFRAGMENT_H_
#define LAYERFRAGMENT_H_

#include <SFML/Graphics.hpp>
#include <tmxparser/Tmx.h>

#include "./tileset.h"

class LayerFragment: public sf::Drawable, public sf::Transformable {
 public:
  LayerFragment(TileSet& tileset, bool animated): tileset(tileset),
                                                  animated(animated) {
     vertices.setPrimitiveType(sf::Quads);
  }
  ~LayerFragment(){}

  void add(Quad quad) {
    for (int i = 0; i < 4; i++) {
      vertices.append(quad[i]);
    }
  }

  void next_frame() {
    if (animated)
      frame = (frame + 1 ) % 2;
  }

 private:
  virtual void draw(sf::RenderTarget& target,
                             sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    //draw
    states.texture = &tileset.getTexture(frame);
    target.draw(vertices, states);
  }

  TileSet& tileset;
  sf::VertexArray vertices;

  bool animated;
  int frame{0};
};

#endif  // LAYERFRAGMENT_H_
