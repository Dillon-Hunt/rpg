#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "raylib.h"

#include <map>
#include <vector>

class GameObject {
    protected:
        Texture2D texture;
        Vector2 position;
        int width;
        int height;

    public:
        GameObject() {};

        GameObject(const Texture& texture, const Vector2& position, int width, int height) : texture(texture), position(position), width(width), height(height) {};

        void setTexture(const Texture2D& t, int w, int h);

        template <typename T>
        bool checkCollision(const T& entity) const {
            return CheckCollisionRecs(getCollisionShape(), entity.getCollisionShape());
        };

        template <typename T>
        bool checkCollisions(const std::vector<std::unique_ptr<T>>& entities) const {
            Rectangle collisionShape = getCollisionShape();

            for (const std::unique_ptr<T>& entity : entities) {
                if (CheckCollisionRecs(collisionShape, entity->getCollisionShape())) {
                    return true;
                }
            }

            return false;
        };

        template <typename T>
        bool checkCollisions(const std::map<std::pair<int, int>, std::unique_ptr<GameObject>>& gameObjects) const {
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

        virtual void draw() const;

        void unloadTexture();

        virtual ~GameObject() {};

        virtual void update(const GameObject& /*player*/) {};
};

#endif // GAME_OBJECT_H
