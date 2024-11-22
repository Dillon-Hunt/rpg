#include "NPC.h"

#include "raymath.h"

#include "Config.h"

void NPC::addWaypoint(const Vector2& w) {
    waypoints.push_back(w);
}

void NPC::update(const GameObject& player) {
    Vector2 oldPosition = position;

    position = Vector2MoveTowards(position, waypoints.at(waypoint),  NPC_SPEED * SCALE);

    if (checkCollision<GameObject>(player)) {
        position = oldPosition;
    }

    if (Vector2Equals(position, waypoints.at(waypoint))) {
        waypoint++;

        if (waypoint == (int) waypoints.size()) {
            waypoint = 0;
        }
    }
}
