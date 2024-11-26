#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "game-objects/entities/Player.h"
#include "Scene.h"

#include <map>
#include <memory>

class SceneManager {
    private:
        std::shared_ptr<Player> player;
        std::map<int, std::shared_ptr<Scene>> scenes;
        std::shared_ptr<Scene> scene;
        int lastID;

    public:
        SceneManager(std::shared_ptr<Player> player) : player(player), scene(nullptr), lastID(-1) {}

        int createScene();

        std::shared_ptr<Scene> getScene() const;

        void setScene(int id);

        void removeScene(int id);

        ~SceneManager() {}
};

#endif // SCENE_MANAGER_H
