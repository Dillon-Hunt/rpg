#ifndef MOUSE_H
#define MOUSE_H

#include "utils/grid.h"

#include <iostream>

class Mouse {
    private:
        bool selected;
        Point position;
        Vector2 selectedTile;
        Texture2D cursorTexture;
        Texture2D selectedTexture;

    public:
        Mouse() : selected(false), position({ 0, 0 }) {
            std::cout << "Loading texture: resources/cursor.png" << std::endl;
            std::cout << "Loading texture: resources/selected-tile.png" << std::endl;
            cursorTexture = LoadTexture("resources/cursor.png");
            selectedTexture = LoadTexture("resources/selected-tile.png");
        }

        Point getGridPosition();

        bool clickHandler(const Point& gridPosition);

        void update(Vector2& cameraOffset);

        void draw(Vector2 cameraOffset) const;

        ~Mouse() {
            std::cout << "Unloading texture: resources/cursor.png" << std::endl;
            std::cout << "Unloading texture: resources/selected-tile.png" << std::endl;
            UnloadTexture(cursorTexture);
            UnloadTexture(selectedTexture);
        }

};

#endif // MOUSE_H
