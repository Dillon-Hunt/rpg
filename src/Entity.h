#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

#include <vector>

class Entity {
    protected:
        Texture2D texture;
        Vector2 position;
        int width;
        int height;

    public:
        Entity() {};

        Entity(const Texture& texture, const Vector2& position) : texture(texture), position(position) {};

        void setTexture(const Texture2D& t, int w, int h);

        void move(const Vector2& position);

        void slide(const Vector2& delta);
        
        bool checkCollision(const Entity& entity) const;

        bool checkCollisions(const std::vector<std::unique_ptr<Entity>>& entities) const;

        Vector2 getPosition() const;

        int getX() const;

        int getY() const;

        int getChunkX() const;

        int getChunkY() const;

        virtual Rectangle getCollisionShape() const;
        
        virtual Vector2 getOrigin() const;

        void draw() const;

        void unloadTexture();

        virtual ~Entity() {};

        virtual void update(const Entity& /*player*/) {};
};

#endif // ENTITY_H
