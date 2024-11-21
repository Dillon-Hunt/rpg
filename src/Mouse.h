#ifndef MOUSE_H
#define MOUSE_H

#include "raylib.h"

class Mouse {
    private:
        int x;
        int y;
        int width;
        int height;
        Color color;
        bool selected;

    public:
        Mouse(int x, int y, int width = 1, int height = 1, Color color = BLUE) : x(x), y(y), width(width), height(height), color(color), selected(false) {};

        void select();

        void deselect();

        bool isSelected() const;

        int getX() const;

        int getY() const;

        int getRelativeX() const;

        int getRelativeY() const;

        int getChunkX() const;

        int getChunkY() const;

        void updatePosition(int offsetX, int offsetY);

        void draw() const;
};

#endif // MOUSE_H
