#ifndef MOUSE_H
#define MOUSE_H

#include "utils/grid.h"
#include "utils/mode.h"
#include "EventManager.h"

#include <iostream>

/**
 * Handles mouse cursor
 */
class Mouse {
    private:
        bool selected;
        Point position;
        Vector2 selectedTile;
        Texture2D cursorTexture;
        Texture2D selectedTexture;
        Mode& mode;

    public:
        /**
         * Constructs a new mouse instance
         */
        Mouse(Mode& mode) : selected(false), position({ 0, 0 }), mode(mode) {
            std::cout << "Loading texture: resources/cursor.png" << std::endl;
            std::cout << "Loading texture: resources/selected-tile.png" << std::endl;
            cursorTexture = LoadTexture("resources/cursor.png");
            selectedTexture = LoadTexture("resources/selected-tile.png");

            EventManager::get().addListener<Mouse>(ESCAPE, this, [this]() {
                selected = false;
            });
        }

        /**
         * Retives the tile position of the mouse
         */
        Point getGridPosition();

        /**
         * Handles clicks by selecting and deselecting tiles
         *
         * @returns true iff the click was handled
         */
        bool clickHandler();

        /**
         * Updates mouse position
         *
         * @param cameraOffset the offset of the frame
         */
        void update(Vector2& cameraOffset);

        /**
         * Draws selection around selected tile
         */
        void drawSelector() const;

        /**
         * Draws the mouse cursor
         */
        void drawCursor() const;

        /**
         * Deconstructs mouse instance
         */
        ~Mouse() {
            std::cout << "Unloading texture: resources/cursor.png" << std::endl;
            std::cout << "Unloading texture: resources/selected-tile.png" << std::endl;
            UnloadTexture(cursorTexture);
            UnloadTexture(selectedTexture);

            EventManager::get().removeListeners(this);
        }

};

#endif // MOUSE_H
