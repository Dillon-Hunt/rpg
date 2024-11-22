#ifndef TILE_H
#define TILE_H

#include "Pallet.h"

#include <array>

class Tile {
    public:
        Tile() {};

        void draw(int x, int y, const std::array<int, 4>& keys, const Pallet& pallet) const;
};

#endif // TILE_H
