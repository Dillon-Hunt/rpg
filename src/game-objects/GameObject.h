#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "raylib.h"

#include <vector>
#include <memory>

class Chunk;

class GameObject {
    protected:
        int id;
        Vector2 position;
        Texture2D& texture;
        std::weak_ptr<Chunk> parent;
        std::vector<std::unique_ptr<GameObject>> children;

    public:
        GameObject(int id, Vector2 position, Texture2D& texture, std::shared_ptr<Chunk> parent) : id(id), position(position), texture(texture), parent(parent) {}

        int getID() const;

        Vector2 getPosition() const;

        std::shared_ptr<Chunk> getParent() const;

        void setTexture(Texture2D& t);

        void setParent(std::shared_ptr<Chunk> chunk);

        void addChild(std::unique_ptr<GameObject>& child);

        virtual void update();

        virtual void draw() const;

        virtual ~GameObject() {}
};

#endif // GAME_OBJECT_H
