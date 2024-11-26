#include "Scene.h"

#include "utils/grid.h"

int Scene::getID() const {
    return id;
}

void Scene::activate() {
    active = true;
}

void Scene::deactivate() {
    active = false;
}

void Scene::setTile(Point p, int tile) {
    Point position = GridPositionToChunkPosition(p); 

    auto it = chunks->find({ position.x, position.y });

    if (it == chunks->end()) {
        loadChunks(position);
    }
    
    chunks->at({ position.x, position.y }).get()->setTile(p.x - position.x * CHUNK_SIZE, p.y - position.y * CHUNK_SIZE, tile);
}

void Scene::placeObject(Point p, int object) {
    Point position = GridPositionToChunkPosition(p); 

    auto it = chunks->find({ position.x, position.y });

    if (it == chunks->end()) {
        loadChunks(position);
    }
    
    chunks->at({ position.x, position.y }).get()->placeObject(p.x - position.x * CHUNK_SIZE, p.y - position.y * CHUNK_SIZE, object);
}

void Scene::loadChunks(Point origin) {
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            std::pair<int, int> position = { origin.x + x, origin.y + y };

            auto iterator = chunks->find(position);

            if (iterator == chunks->end()) {
                chunks->emplace(position, std::make_shared<Chunk>(Point { position.first, position.second }, chunks));
            }
        }
    }
}

void Scene::update() {
    Point origin = Vector2ToChunkPosition(player->getPosition());

    // Create chunks if necessary
    loadChunks(origin);

    // Update chunks

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            chunks->at({ origin.x + x, origin.y + y }).get()->update();
        }
    }
}

void Scene::draw() const {
    Point origin = Vector2ToChunkPosition(player->getPosition());

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            chunks->at({ origin.x + x, origin.y + y }).get()->drawTiles();
        }
    }

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            chunks->at({ origin.x + x, origin.y + y }).get()->drawObjects();
        }
    }
}
