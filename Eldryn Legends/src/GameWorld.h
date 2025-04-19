#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include "Map.h"
#include "Slime.h"
#include "Warrior.h"
#include "Camera.h"

class Map;
class Warrior;
class Slime;

class GameWorld{
private:
    std::unique_ptr<Warrior> player;
    std::unique_ptr<Slime> enemySlime;
    std::unique_ptr<Map> gameMap;
    Camera camera;
    int** mapData;
public:
    GameWorld(SDL_Renderer* renderer);
    ~GameWorld();

    void map();
    void render(SDL_Renderer* renderer);
    void update(float dt);
    void handleInput(float dt, const Uint8* keys);
};