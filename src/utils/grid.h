#ifndef GRID_H
#define GRID_H

#include "raylib.h"

struct Point {
    int x;
    int y;
};

Point Vector2ToGridPosition(Vector2 v);

Point Vector2ToChunkPosition(Vector2 v);

Point GridPositionToChunkPosition(Point p);

Vector2 GridPositionToVector2(Point p);

#endif // GRID_H
