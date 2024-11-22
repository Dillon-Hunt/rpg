#include "Tile.h"

void Tile::draw(int x, int y, const std::array<int, 4>& keys, const Pallet& pallet) const {
    pallet.drawTile(x, y, keys);
}
