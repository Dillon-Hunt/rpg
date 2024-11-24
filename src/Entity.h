#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "raylib.h"

#include <map>
#include <vector>

// Forward declaration of Chunk to prevent circular dependency
class Chunk;

class Entity {
    protected:
        Texture2D texture;
        Vector2 position;

    public:
        Entity() {};

        Entity(const Texture& texture, const Vector2& position) : texture(texture), position(position) {};

        void setTexture(const Texture2D& t);

        void move(const Vector2& position);

        void slide(const Vector2& delta);

        bool checkCollision(const Entity& entity) const {
            return CheckCollisionRecs(getCollisionShape(), entity.getCollisionShape());
        };

        bool checkCollisions(const std::vector<std::unique_ptr<Entity>>& entities) const {
            Rectangle collisionShape = getCollisionShape();

            for (const std::unique_ptr<Entity>& entity : entities) {
                if (CheckCollisionRecs(collisionShape, entity->getCollisionShape())) {
                    return true;
                }
            }

            return false;
        };

        bool checkCollisions(const std::map<std::pair<int, int>, std::unique_ptr<Entity>>& gameObjects) const {
            Rectangle collisionShape = getCollisionShape();

            for (auto& object : gameObjects) {
                if (CheckCollisionRecs(collisionShape, object.second->getCollisionShape())) {
                    return true;
                }
            }

            return false;
        };

        Vector2 getPosition() const;

        int getX() const;

        int getY() const;

        int getChunkX() const;

        int getChunkY() const;

        virtual Rectangle getCollisionShape() const;
        
        virtual Vector2 getOrigin() const;

        virtual Rectangle getDestinationShape() const;

        virtual void draw() const;

        void unloadTexture();

        virtual ~Entity() {};

        virtual void update(const std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& /*chunks*/, const Entity& /*player*/) {};
};

#endif // GAME_OBJECT_H
