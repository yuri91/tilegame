#ifndef LAYERFRAGMENT_H_
#define LAYERFRAGMENT_H_

#include <SFML/Graphics.hpp>
#include <tmxparser/Tmx.h>

#include "./tileset.h"

class LayerFragment: public sf::Drawable, public sf::Transformable {
 public:
  LayerFragment(TileSet& tileset): tileset(tileset){
     vertices.setPrimitiveType(sf::Quads);
  }
  ~LayerFragment(){}

  void add(Quad quad) {
    for (int i = 0; i < 4; i++) {
      vertices.append(quad[i]);
    }
  }
 private:
  virtual void draw(sf::RenderTarget& target,
                             sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    //draw
    states.texture = &tileset.getTexture();
    target.draw(vertices, states);
  }

  TileSet& tileset;
  sf::VertexArray vertices;
};

#endif  // LAYERFRAGMENT_H_
