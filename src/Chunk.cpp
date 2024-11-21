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

void Chunk::setTexture(int col, int row, int key) {
    textures[col][row] = key;
}

int Chunk::getKey(int col, int row, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks) const {
    if (row == -1 && col == -1) return chunks.at(std::make_pair(x - 1, y - 1))->getKey(CHUNK_SIZE - 1, CHUNK_SIZE - 1, chunks);
    if (col == -1) return chunks.at(std::make_pair(x - 1, y))->getKey(CHUNK_SIZE - 1, row, chunks);
    if (row == -1) return chunks.at(std::make_pair(x, y - 1))->getKey(col, CHUNK_SIZE - 1, chunks);

    return keys[col][row];
}

int Chunk::getTexture(int col, int row, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks) const {
    if (row == -1 && col == -1) return chunks.at(std::make_pair(x - 1, y - 1))->getTexture(CHUNK_SIZE - 1, CHUNK_SIZE - 1, chunks);
    if (col == -1) return chunks.at(std::make_pair(x - 1, y))->getTexture(CHUNK_SIZE - 1, row, chunks);
    if (row == -1) return chunks.at(std::make_pair(x, y - 1))->getTexture(col, CHUNK_SIZE - 1, chunks);
    return textures[col][row];
}

void Chunk::set(int col, int row, int key, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks) {
    keys[col][row] = 1;

    textures[col][row] = key;

    if (row == 0 && col == 0) {
        chunks.at(std::make_pair(x - 1, y - 1))->setTexture(CHUNK_SIZE - 1, CHUNK_SIZE - 1, key);
    } else {
        if (col == 0) {
            chunks.at(std::make_pair(x - 1, y))->setTexture(CHUNK_SIZE - 1, row, key);
            chunks.at(std::make_pair(x - 1, y))->setTexture(CHUNK_SIZE - 1, row - 1, key);
        } else {
            textures[col - 1][row] = key;
        }

        if (row == 0) {
            chunks.at(std::make_pair(x, y - 1))->setTexture(col, CHUNK_SIZE - 1, key);
            chunks.at(std::make_pair(x, y - 1))->setTexture(col - 1, CHUNK_SIZE - 1, key);
        } else {
            textures[col][row - 1] = key;
        }

        if (row != 0 && col != 0) {
            textures[col - 1][row - 1] = key;
        }
    }
}

void Chunk::draw(const Pallet& pallet, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks) const {
    for (int col = 0; col < CHUNK_SIZE; col++) {
        for (int row = 0; row < CHUNK_SIZE; row++) {
            tiles[col][row].draw(
                x * CHUNK_SIZE + col,
                y * CHUNK_SIZE + row,
                getTexture(col - 1, row - 1, chunks),
                {
                    getKey(col - 1, row - 1, chunks),
                    getKey(col, row - 1, chunks),
                    getKey(col, row, chunks),
                    getKey(col - 1, row, chunks),
                },
                pallet
            );
        }
    }
}
