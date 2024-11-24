#include "NPC.h"

#include "raymath.h"

#include "Config.h"

void NPC::addWaypoint(const Vector2& w) {
    waypoints.push_back(w);
}

void NPC::update(const std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks, const Entity& player) {
    Vector2 previousPosition = position;

    position = Vector2MoveTowards(position, waypoints.at(waypoint),  NPC_SPEED * SCALE);

    // Collision Detection

    if (
        chunks.at(
            std::make_pair(
                getChunkX(),
                getChunkY()
            )
        )->checkCollision(*this)
    ) {
        position = previousPosition;
    } else if (Vector2Equals(position, waypoints.at(waypoint))) {
        waypoint++;

        if (waypoint == (int) waypoints.size()) {
            waypoint = 0;
        }
    }
}
