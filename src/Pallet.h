#ifndef PALLET_H
#define PALLET_H

#include "raylib.h"

#include <map>

class Pallet {
    private:
        std::map<int, std::shared_ptr<Texture2D>> textures;

    public:
        void loadTexture(int key, const char* path);

        const std::shared_ptr<Texture2D> getTexture(int key) const;

        int getTextureFromPallet() const;

        void renderPallet() const;

        Vector2 getImageSourcePosition(const std::array<int, 4>& keys) const;

        void drawTile(int x, int y, int key, const std::array<int, 4>& keys) const;

        void unloadTextures();
};

#endif // PALLET_H
