#include "grid.h"

#include "config.h"

Point Vector2ToGridPosition(Vector2 v) {
    return Point { (int) (v.x / TILE_SIZE + ( v.x > 0 ? 0.5f : -0.5f )), (int) (v.y / TILE_SIZE + ( v.y > 0 ? 0.5f : -0.5f )) };
}

Point GridPositionToChunkPosition(Point p) {
    return Point { p.x / CHUNK_SIZE - ( p.x < 0 ? 1 : 0 ) + ( p.x % CHUNK_SIZE == 0 && p.x < 0 ? 1 : 0 ), p.y / CHUNK_SIZE - ( p.y < 0 ? 1 : 0 ) + ( p.y % CHUNK_SIZE == 0 && p.y < 0 ? 1 : 0 ) };
}

Point Vector2ToChunkPosition(Vector2 v) {
    return GridPositionToChunkPosition(Vector2ToGridPosition(v));
}

Vector2 GridPositionToVector2(Point p) {
    return Vector2 { (float) p.x * TILE_SIZE, (float) p.y * TILE_SIZE };
}
