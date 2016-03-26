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

#ifndef LAYERFRAGMENT_H_
#define LAYERFRAGMENT_H_

#include <SFML/Graphics.hpp>
#include <tmxparser/Tmx.h>

#include "tile_manager/tileset.h"

namespace Tm {

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

}  // namespace Tm

#endif  // LAYERFRAGMENT_H_
