#ifndef PALLET_H
#define PALLET_H

#include "raylib.h"

#include <map>

struct IntPair {
    int min;
    int max;
};

class Pallet {
    private:
        std::map<int, std::pair<std::shared_ptr<Texture2D>, bool>> textures;
        int countBase{ 0 };

    public:
        void loadTexture(int key, const char* path, bool isBase);

        const std::shared_ptr<Texture2D> getTexture(int key) const;

        int getTextureFromPallet() const;

        void renderPallet() const;
        
        IntPair getMinMax(const std::array<int, 4>& keys) const;

        Vector2 getImageSourcePosition(const std::array<int, 4>& keys) const;

        const std::shared_ptr<Texture2D> getTileTexture(const std::array<int, 4>& keys) const;

        void drawTile(int x, int y, const std::array<int, 4>& keys) const;

        void unloadTextures();
};

#endif // PALLET_H
