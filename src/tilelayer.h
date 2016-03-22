#ifndef TILELAYER_H_
#define TILELAYER_H_

#include <SFML/Graphics.hpp>
#include <tmxparser/Tmx.h>

#include <vector>
#include <map>

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


class TileLayer : public sf::Drawable, public sf::Transformable {
 public:
  bool load(const Tmx::TileLayer& tileLayer,
            std::vector<TileSet>& tileSets, int width, int height);

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  std::map<int, LayerFragment> m_fragments;

};

#endif  // TILELAYER_H_
