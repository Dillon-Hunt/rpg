#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "raylib.h"

#include "../Pallet.h"

#include <vector>
#include <memory>

class Chunk;

class GameObject {
    protected:
        Asset id;
        Vector2 position;
        bool collidable;
        Rectangle collider;
        const Texture2D* texture;
        std::weak_ptr<Chunk> parent;
        std::vector<std::shared_ptr<GameObject>> children;

    public:
        GameObject(Asset id, Vector2 position, std::shared_ptr<Chunk> parent) : id(id), position(position), collidable(Pallet::get().isCollidable(id)), collider(Pallet::get().getColider(id)), texture(Pallet::get().getTexture(id)), parent(parent) {}

        Asset getID() const;

        Vector2 getPosition() const;

        std::shared_ptr<Chunk> getParent() const;

        void setParent(std::shared_ptr<Chunk> chunk);

        void addChild(std::shared_ptr<GameObject>& child);

        bool isCollidable() const;

        virtual const Rectangle getColider() const;

        virtual void update();

        virtual void draw() const;

        virtual ~GameObject() {}
};

#endif // GAME_OBJECT_H
