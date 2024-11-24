#include "Enemy.h"

#include "raymath.h"

#include "Config.h"

void Enemy::updateTarget() {
    float spawnAngle = std::atan2(spawn.y - position.y, spawn.x - position.x);
    float randomAngle = (getRandomNumber() - 0.5f) * PI / 4.0f + direction;
    float biasStrength = Clamp(Vector2Distance(spawn, position) / (ENTITY_MAXIMUM_WANDER_RADIUS * CELL_SIZE * SCALE), 0.0f, 1.0f);
    float angle = (1.0f - biasStrength) * randomAngle + biasStrength * spawnAngle;
    int distance = (getRandomNumber() * (SPAWN_RADIUS - NO_SPAWN_RADIUS) + NO_SPAWN_RADIUS) * CELL_SIZE * SCALE;

    target = { position.x + distance * cos(angle), position.y + distance * sin(angle) };
}

void Enemy::update(const std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& /*chunks*/, const Entity& player) {
    float distance = Vector2Distance(player.getPosition(), position);

    if (distance < ENEMY_DETECTION_RADIUS * CELL_SIZE * SCALE) {
        locked = true;
    }

    if (distance > ENEMY_ESCAPE_RADIUS * CELL_SIZE * SCALE) {
        if (locked) {
            updateTarget();
        }

        locked = false;
    }

    if (locked) {
        target = player.getPosition();
    }

    float targetAngle = std::atan2(target.y - position.y, target.x - position.x);
    float delta = std::atan2(std::sin(targetAngle - direction), std::cos(targetAngle - direction));

    direction += Clamp(delta, -0.05f, 0.05f);
    position += Vector2 { std::cos(direction), std::sin(direction) } * (locked ? ENEMY_TARGET_SPEED : ENEMY_IDLE_SPEED);

    if (Vector2Distance(position, target) < CELL_SIZE * SCALE) {
        updateTarget();
    }
}

Vector2 Enemy::getOrigin() const {
    return {
        -texture.width * SCALE / 2.0f,
        0
        
    };
}

void Enemy::draw() const {
    DrawTexturePro(
        texture,
        {
            0,
            0,
            (float) texture.width,
            (float) texture.height
        },
        getDestinationShape(),
        getOrigin(),
        0.0f,
        WHITE
    );

    if (SHOW_ENEMY_TARGETING) {
        DrawLineEx(position, { position.x + CELL_SIZE * cos(direction), position.y + CELL_SIZE * sin(direction) }, 1.0f * SCALE, RED);
        DrawCircle(target.x, target.y, 5 * SCALE, locked ? ORANGE : BLUE);
        DrawCircle(position.x, position.y, 5 * SCALE, RED);
    }
}
