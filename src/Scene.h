#ifndef SCENE_H
#define SCENE_H

#include "game-objects/entities/Player.h"
#include "EventManager.h"
#include "Chunk.h"

#include <map>
#include <utility>
#include <memory>

class Scene {
    private:
        int id;
        bool active;
        std::shared_ptr<Player> player;
        std::shared_ptr<std::map<std::pair<int, int>, std::shared_ptr<Chunk>>> chunks;

    public:
        Scene(int id, std::shared_ptr<Player> player) : id(id), active(false), player(player), chunks(std::make_shared<std::map<std::pair<int, int>, std::shared_ptr<Chunk>>>()) {
            EventManager::get().addListener<Scene, std::pair<Point, int>>(
                PLACE_TILE,
                this,
                [this](std::pair<Point, int> data) {
                    if (active) {
                        setTile(data.first, data.second);
                    }
                }
            );

            EventManager::get().addListener<Scene, std::pair<Point, int>>(
                PLACE_OBJECT,
                this,
                [this](std::pair<Point, int> data) {
                    if (active) {
                        placeObject(data.first, data.second);
                    }
                }
            );
        }

        int getID() const;

        void activate();

        void deactivate();

        void setTile(Point p, int tile);

        void placeObject(Point p, int object);

        void loadChunks(Point origin);

        void update();

        void draw() const;

        ~Scene() {}
};

#endif // SCENE_H
