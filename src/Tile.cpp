#include "Tile.h"

void Tile::draw(int x, int y, int key, const std::array<int, 4>& keys, const Pallet& pallet) const {
    pallet.drawTile(x, y, key, keys);
}
