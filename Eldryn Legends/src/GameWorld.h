#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include <list>
#include "Map.h"
#include "Goblin.h"  // Alterado para Goblin
#include "Warrior.h"
#include "Camera.h"
#include "GameManager.h"

class Map;
class Warrior;
class Goblin;  // Alterado para Goblin

class GameWorld{
private:
    std::unique_ptr<Warrior> player;
    std::list<std::unique_ptr<Goblin>> enemyGoblins;  // Alterado para Goblin
    std::unique_ptr<Map> gameTerrain1;
    std::unique_ptr<Map> gameTerrain2;
    int** mapTerrain1;
    int** mapTerrain2;
    Camera camera;
public:
    GameWorld(SDL_Renderer* renderer, TextureManager& textureManager);
    ~GameWorld();

    void map();
    void render(SDL_Renderer* renderer);
    void update(float dt, const Uint8* keys);
    void handleInput(const SDL_Event& event);
};
