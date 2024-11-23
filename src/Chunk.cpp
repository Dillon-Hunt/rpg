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
    tileTexture[col][row] = 0;
}

int Chunk::getTileTexture(int col, int row) const {
    if (row == -1 && col == -1) return chunks.at(std::make_pair(x - 1, y - 1))->getTileTexture(CHUNK_SIZE - 1, CHUNK_SIZE - 1);
    if (col == -1) return chunks.at(std::make_pair(x - 1, y))->getTileTexture(CHUNK_SIZE - 1, row);
    if (row == -1) return chunks.at(std::make_pair(x, y - 1))->getTileTexture(col, CHUNK_SIZE - 1);
    return tileTexture[col][row];
}

int Chunk::getGameObjectTexture(int col, int row) const {
    if (row == -1 && col == -1) return chunks.at(std::make_pair(x - 1, y - 1))->getGameObjectTexture(CHUNK_SIZE - 1, CHUNK_SIZE - 1);
    if (col == -1) return chunks.at(std::make_pair(x - 1, y))->getGameObjectTexture(CHUNK_SIZE - 1, row);
    if (row == -1) return chunks.at(std::make_pair(x, y - 1))->getGameObjectTexture(col, CHUNK_SIZE - 1);
    return gameObjectTexture[col][row];
}

void Chunk::set(int col, int row, int texture) {
    tileTexture[col][row] = texture;
}

void Chunk::place(int col, int row, int texture) {
    gameObjectTexture[col][row] = texture;
}

void Chunk::drawTiles() const {
    for (int col = 0; col < CHUNK_SIZE; col++) {
        for (int row = 0; row < CHUNK_SIZE; row++) {
            pallet.drawTile(
                x * CHUNK_SIZE + col,
                y * CHUNK_SIZE + row,
                {
                    getTileTexture(col - 1, row - 1),
                    getTileTexture(col, row - 1),
                    getTileTexture(col, row),
                    getTileTexture(col - 1, row),
                }
            );
        }
    }
}

Vector2 Chunk::getGameObjectSourcePosition(const std::array<int, 4>& keys, int key) const {
    static const std::map<std::array<int, 4>, Vector2> mapping = {
        // NORTH, EAST, SOUTH, WEST
        {{ NONE, NONE, NONE, NONE }, { 0, 0 }},
        {{ NONE, NONE, NONE, 1 }, { 3, 0 }},
        {{ NONE, NONE, 1, NONE }, { 0, 1 }},
        {{ NONE, NONE, 1, 1 }, { 3, 1 }},
        {{ NONE, 1, NONE, NONE }, { 1, 0 }},
        {{ NONE, 1, NONE, 1 }, { 2, 0 }},
        {{ NONE, 1, 1, NONE }, { 1, 1 }},
        {{ NONE, 1, 1, 1 }, { 2, 1 }},
        {{ 1, NONE, NONE, NONE }, { 0, 3 }},
        {{ 1, NONE, NONE, 1 }, { 3, 3 }},
        {{ 1, NONE, 1, NONE }, { 0, 2 }},
        {{ 1, NONE, 1, 1 }, { 3, 2 }},
        {{ 1, 1, NONE, NONE }, { 1, 3 }},
        {{ 1, 1, NONE, 1 }, { 2, 3 }},
        {{ 1, 1, 1, NONE }, { 1, 2 }},
        {{ 1, 1, 1, 1 }, { 2, 2 }},
    };

    std::array<int, 4> masked = { NONE, NONE, NONE, NONE };

    if (masked != keys) {
        for (int i = 0; i < 4; i++) {
            if (keys[i] == key) {
                masked[i] = 1;
            }
        }
    }

    std::cout << keys[0] << " " << keys[1] << " " << keys[2] << " " << keys[3] << std::endl;
    std::cout << masked[0] << " " << masked[1] << " " << masked[2] << " " << masked[3] << std::endl;
    std::cout << std::endl;

    return mapping.find(masked)->second;
}

void Chunk::drawGameObjects() const {
    for (int col = 0; col < CHUNK_SIZE; col++) {
        for (int row = 0; row < CHUNK_SIZE; row++) {
            if (gameObjectTexture[col][row] == NONE) continue;

            Vector2 sourceImagePosition = getGameObjectSourcePosition({
                getGameObjectTexture(col, row - 1),
                getGameObjectTexture(col + 1, row),
                getGameObjectTexture(col, row + 1),
                getGameObjectTexture(col - 1, row)
            }, gameObjectTexture[col][row]);

            DrawTexturePro(
                gameObjectTextures.at(gameObjectTexture[col][row]),
                {
                    sourceImagePosition.x * CELL_SIZE,
                    sourceImagePosition.y * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                },
                {
                    (col + x * CHUNK_SIZE) * CELL_SIZE * SCALE,
                    (row + y * CHUNK_SIZE) * CELL_SIZE * SCALE,
                    CELL_SIZE * SCALE,
                    CELL_SIZE * SCALE
                },
                {
                    0.0f,
                    0.0f
                },
                0.0f,
                WHITE
            );
        }
    }
}

void Chunk::draw() const {
    drawTiles();
    drawGameObjects();
}

void Chunk::unloadTextures() {
    for (Texture2D& texture : gameObjectTextures) {
        UnloadTexture(texture);
    }
}
