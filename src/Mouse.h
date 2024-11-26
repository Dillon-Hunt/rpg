#ifndef MOUSE_H
#define MOUSE_H

#include "utils/config.h"
#include "utils/grid.h"
#include "Pallet.h"

class Mouse {
    private:
        Point position;
        PalletType type;
        int selectedTile;

    public:
        Mouse() : position({ 0, 0 }), selectedTile(DIRT) {}

        Point getGridPosition();

        void update(Vector2& cameraOffset);

        void draw() const;

        ~Mouse() {}

};

#endif // MOUSE_H
