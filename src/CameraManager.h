#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "raylib.h"

#include "utils/config.h"
#include "game-objects/Entity.h"

#include <memory>

class CameraManager {
    private:
        std::shared_ptr<Camera2D> camera;
        std::shared_ptr<Entity> target;

    public:
        CameraManager()
            : camera(std::make_shared<Camera2D>()), target(nullptr) {
            camera->offset = Vector2 { WIDTH / 2.0f, HEIGHT / 2.0f };
            camera->target = Vector2 { 0.0f, 0.0f };
            camera->rotation = 0.0f;
            camera->zoom = SCALE;

        }

        std::shared_ptr<Camera2D> getCamera() const;

        Vector2 getOffset() const;

        void follow(std::shared_ptr<Entity> entity);

        void update();

        ~CameraManager() {}
};

#endif // CAMERA_MANAGER_H
