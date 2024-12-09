#ifndef MOUSE_H
#define MOUSE_H

#include "utils/grid.h"
#include "Pallet.h"

class Mouse {
    private:
        Point position;
        PalletType type;
        Tile selectedTile;
        Texture2D texture;

    public:
        Mouse() : position({ 0, 0 }), selectedTile(DIRT) {
            std::cout << "Loading texture: resources/cursor.png" << std::endl;
            texture = LoadTexture("resources/cursor.png");
        }

        Point getGridPosition();

        void update(Vector2& cameraOffset);

        void draw(Vector2 cameraOffset) const;

        ~Mouse() {
            std::cout << "Unloading texture: resources/cursor.png" << std::endl;
            UnloadTexture(texture);
        }

};

#endif // MOUSE_H
