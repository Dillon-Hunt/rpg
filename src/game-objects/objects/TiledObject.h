#ifndef TILED_OBJECT_H
#define TILED_OBJECT_H

#include "../Object.h"

#include "../../utils/grid.h"

#include <memory>

class TiledObject : public Object {
    public:
        TiledObject(Asset id, Vector2 position, std::shared_ptr<Chunk> parent) : Object(id, position, parent) {}

        void update() override;

        Point getObjectSource() const;

        void draw() const override;

        ~TiledObject() {}
};

#endif // TILED_OBJECT_H
