#include "CameraManager.h"

#include "raymath.h"

std::shared_ptr<Camera2D> CameraManager::getCamera() const {
    return camera;
}

Vector2 CameraManager::getOffset() const {
    return Vector2 { camera->offset.x - camera->target.x * SCALE, camera->offset.y - camera->target.y * SCALE };
}


void CameraManager::follow(std::shared_ptr<Entity> entity) {
    target = entity;
}

void CameraManager::update() {
    if (target != nullptr) {
        float distance = Vector2Distance(camera->target, target->getPosition());
        float deceleration = Clamp(distance / (TILE_SIZE * CAMERA_DRIFT_RADIUS), 0, 1);
        camera->target = Vector2MoveTowards(camera->target, target->getPosition(), PLAYER_SPEED * deceleration);
    } else {
        camera->target = { 0, 0 };
    }
}
