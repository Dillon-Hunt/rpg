#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "raylib.h"

#include "utils/config.h"
#include "game-objects/Entity.h"

#include <memory>

/**
 * Manages camera to follow an entity
 */
class CameraManager {
    private:
        std::shared_ptr<Camera2D> camera;
        std::shared_ptr<Entity> target;

    public:
        /**
         * Constructs a new CameraManager instance
         */
        CameraManager()
            : camera(std::make_shared<Camera2D>()), target(nullptr) {
            camera->offset = Vector2 { WIDTH / 2.0f, HEIGHT / 2.0f };
            camera->target = Vector2 { 0.0f, 0.0f };
            camera->rotation = 0.0f;
            camera->zoom = SCALE;

        }

        /**
         * Retrives a shared_ptr to the camera
         *
         * @returns a shared_ptr to the camera
         */
        std::shared_ptr<Camera2D> getCamera() const;

        /**
         * Retrives the camera offset from (0, 0)
         *
         * @returns a Vector2 of the camera's offset
         */
        Vector2 getOffset() const;

        /**
         * Sets the entity that should be followed
         *
         * @param entity the entity to follow
         */
        void follow(std::shared_ptr<Entity> entity);

        /**
         * Updates the camera offset such that the followed entity is centred
         */
        void update();

        /**
         * Deconstructor for CameraManager
         */
        ~CameraManager() {}
};

#endif // CAMERA_MANAGER_H
