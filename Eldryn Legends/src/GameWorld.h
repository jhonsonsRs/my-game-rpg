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
        SDL_Texture* playerSpriteAtlasRight, 
        SDL_Texture* playerSpriteAtlasUp, 
        SDL_Texture* playerSpriteAtlasDown, 
        SDL_Texture* playerSpriteAtlasRight2, 
        SDL_Texture* playerSpriteAtlasUp2, 
        SDL_Texture* playerSpriteAtlasDown2,
        SDL_Texture* playerSpriteAtlasHitUp,
        SDL_Texture* playerSpriteAtlasHitDown,
        SDL_Texture* playerSpriteAtlasHitRight,

        SDL_Texture* goblinSpriteAtlasRight, 
        SDL_Texture* goblinSpriteAtlasUp, 
        SDL_Texture* goblinSpriteAtlasDown, 
        SDL_Texture* goblinSpriteAtlasRight2, 
        SDL_Texture* goblinSpriteAtlasUp2, 
        SDL_Texture* goblinSpriteAtlasDown2);
    ~GameWorld();

    void map();
    void render(SDL_Renderer* renderer);
    void update(float dt, const Uint8* keys);
    void handleInput(const SDL_Event& event);
};
