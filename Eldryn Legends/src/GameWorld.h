#pragma once
#include <memory>
#include <SDL2/SDL.h>
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
    std::unique_ptr<Goblin> enemyGoblin;  // Alterado para Goblin
    std::unique_ptr<Map> gameTerrain1;
    std::unique_ptr<Map> gameTerrain2;
    int** mapTerrain1;
    int** mapTerrain2;
    Camera camera;
public:
    GameWorld(SDL_Renderer* renderer, 
        SDL_Texture* spriteAtlasRight, 
        SDL_Texture* spriteAtlasUp, 
        SDL_Texture* spriteAtlasDown, 
        SDL_Texture* spriteAtlasRight2, 
        SDL_Texture* spriteAtlasUp2, 
        SDL_Texture* spriteAtlasDown2);
    ~GameWorld();

    void map();
    void render(SDL_Renderer* renderer);
    void update(float dt);
    void handleInput(float dt, const Uint8* keys);
};
