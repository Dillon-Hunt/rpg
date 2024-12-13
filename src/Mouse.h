#ifndef MOUSE_H
#define MOUSE_H

#include "utils/grid.h"
#include "utils/mode.h"
#include "EventManager.h"

#include <iostream>

class Mouse {
    private:
        bool selected;
        Point position;
        Vector2 selectedTile;
        Texture2D cursorTexture;
        Texture2D selectedTexture;
        Mode& mode;

    public:
        Mouse(Mode& mode) : selected(false), position({ 0, 0 }), mode(mode) {
            std::cout << "Loading texture: resources/cursor.png" << std::endl;
            std::cout << "Loading texture: resources/selected-tile.png" << std::endl;
            cursorTexture = LoadTexture("resources/cursor.png");
            selectedTexture = LoadTexture("resources/selected-tile.png");

            EventManager::get().addListener<Mouse>(ESCAPE, this, [this]() {
                selected = false;
            });
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

            EventManager::get().removeListeners(this);
        }

};

#endif // MOUSE_H
