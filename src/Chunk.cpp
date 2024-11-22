#include "Chunk.h"
#include <iostream>

// void Chunk::load(const char* path) {
//     std::ifstream file(path);
//
//     std::string line;
//     int y = 0;
//
//     if (file.is_open()) {
//         while (getline(file, line)) {
//             int x = 0;
//
//             for (char& raw : line) {
//                 int texture = raw - '0';
//                 set(x, y, texture);
//
//                 x++;
//             }
//
//             y++;
//         }
//
//         file.close();
//     } else {
//         throw std::runtime_error("Could not open file: " + std::string(path));
//     }
// }

void Chunk::unset(int col, int row) {
    keys[col][row] = 0;
}

int Chunk::getKey(int col, int row) const {
    if (row == -1 && col == -1) return chunks.at(std::make_pair(x - 1, y - 1))->getKey(CHUNK_SIZE - 1, CHUNK_SIZE - 1);
    if (col == -1) return chunks.at(std::make_pair(x - 1, y))->getKey(CHUNK_SIZE - 1, row);
    if (row == -1) return chunks.at(std::make_pair(x, y - 1))->getKey(col, CHUNK_SIZE - 1);
    return keys[col][row];
}

// int Chunk::getTexture(int col, int row) const {
//     return 2;
// }

// int Chunk::getTexture(int col, int row) const {
//     if (row == -1 && col == -1) return chunks.at(std::make_pair(x - 1, y - 1))->getTexture(CHUNK_SIZE - 1, CHUNK_SIZE - 1);
//     if (col == -1) return chunks.at(std::make_pair(x - 1, y))->getTexture(CHUNK_SIZE - 1, row);
//     if (row == -1) return chunks.at(std::make_pair(x, y - 1))->getTexture(col, CHUNK_SIZE - 1);
//     return textures[col][row];
// }
//
// void Chunk::setTexture(int col, int row, int key) {
//     if (row == -1 && col == -1) chunks.at(std::make_pair(x - 1, y - 1))->setTexture(CHUNK_SIZE - 1, CHUNK_SIZE - 1, key);
//     else if (col == -1) chunks.at(std::make_pair(x - 1, y))->setTexture(CHUNK_SIZE - 1, row, key);
//     else if (row == -1) chunks.at(std::make_pair(x, y - 1))->setTexture(col, CHUNK_SIZE - 1, key);
//     else textures[col][row] = key;
// }

void Chunk::set(int col, int row, int key) {
    keys[col][row] = key;
}

void Chunk::draw() const {
    for (int col = 0; col < CHUNK_SIZE; col++) {
        for (int row = 0; row < CHUNK_SIZE; row++) {
            tiles[col][row].draw(
                x * CHUNK_SIZE + col,
                y * CHUNK_SIZE + row,
                {
                    getKey(col - 1, row - 1),
                    getKey(col, row - 1),
                    getKey(col, row),
                    getKey(col - 1, row),
                },
                pallet
            );
        }
    }
}
