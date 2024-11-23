#ifndef NPC_H
#define NPC_H

#include "Entity.h"

#include <vector>

class NPC : public Entity {
    private:
        std::vector<Vector2> waypoints;
        int waypoint;

    public:
        NPC() : waypoint(0) {};

        NPC(const Texture& texture, const Vector2& position) : Entity(texture, position), waypoint(0) {
            waypoints.push_back(position);
        };

        void addWaypoint(const Vector2& w);

        void update(const GameObject& player) override;
};

#endif // NPC_H
