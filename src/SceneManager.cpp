#include "SceneManager.h"

int SceneManager::createScene() {
    lastID++;
    scenes[lastID] = std::make_shared<Scene>(lastID, player);
    return lastID;
}

std::shared_ptr<Scene> SceneManager::getScene() const {
    return scene;
}

void SceneManager::setScene(int id) {
    if (scene != nullptr) {
        scene->deactivate();
    }

    auto it = scenes.find(id);

    if (it == scenes.end()) {
        scene = nullptr;
    } else {
        scene = it->second;
        scene->activate();
    }

}

void SceneManager::removeScene(int id) {
    auto it = scenes.find(id);

    if (it != scenes.end()) {
        scenes.erase(it);
    }
}
