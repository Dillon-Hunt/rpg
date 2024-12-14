#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "game-objects/entities/Player.h"
#include "Scene.h"

#include <map>
#include <memory>

/**
 * Manages scenes
 */
class SceneManager {
    private:
        std::shared_ptr<Player> player;
        std::map<int, std::shared_ptr<Scene>> scenes;
        std::shared_ptr<Scene> scene;
        int lastID;

    public:
        /**
         * Construcs a new SceneManager
         */
        SceneManager(std::shared_ptr<Player> player) : player(player), scene(nullptr), lastID(-1) {}

        /**
         * Creates a new scene
         *
         * @returns the id of the new scene
         */
        int createScene();

        /**
         * Retives a scene
         *
         * @preturns a shared_ptr to a scene
         */
        std::shared_ptr<Scene> getScene() const;

        /**
         * Deactivates curent scene and activates a new scene
         *
         * @param id of the scene to activate
         */
        void setScene(int id);

        /**
         * Removes a scene from management
         */
        void removeScene(int id);

        /**
         * Deconstructs SceneManager
         */
        ~SceneManager() {}
};

#endif // SCENE_MANAGER_H
