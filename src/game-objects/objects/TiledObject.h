#ifndef TILED_OBJECT_H
#define TILED_OBJECT_H

#include "../Object.h"

#include "../../utils/grid.h"

#include <memory>

class TiledObject : public Object {
    public:
        TiledObject(int id, Vector2 position, Texture2D& texture, std::shared_ptr<Chunk> parent) : Object(id, position, texture, parent) {}

        void update() override;

        Point getObjectSource() const;

        void draw() const override;

        ~TiledObject() {}
};

#endif // TILED_OBJECT_H
