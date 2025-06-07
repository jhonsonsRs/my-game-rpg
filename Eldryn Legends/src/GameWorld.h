#pragma once
#include <memory>
#include <list>
#include <SDL2/SDL.h>
#include "Map.h"
#include "Goblin.h"
#include "Warrior.h"
#include "Camera.h"
#include <SDL2/SDL_ttf.h>
#include "TextureManager.h"  
#include "GameManager.h"
#include "HealthPotion.h"

class Map;
class TextureManager;
class Warrior;
class Goblin;
class HealthPotion;
class GameManager;

class GameWorld{
private:
    std::unique_ptr<Warrior> player;
    std::list<Goblin> enemyGoblins; 
    std::list<HealthPotion> healthPotions;
    std::unique_ptr<Map> gameTerrain1;
    std::unique_ptr<Map> gameTerrain2;
    TextureManager* textureManager;
    int** mapTerrain1;
    int** mapTerrain2;
    Camera camera;

    GameManager* gameManager;
    bool gameOver;
    float restartTimer;

    int goblinsKilled;
    SDL_Texture* healthBarTexture;
    SDL_Texture* healthBarBackgroundTexture;
    SDL_Texture* scoreTexture;
    TTF_Font* font;
public:
    GameWorld(SDL_Renderer* renderer, TextureManager* textureManager);
    ~GameWorld();

    void map();
    void restartGame();
    void spawnRandomGoblins(int count);
    void spawnRandomPotions(int count);
    void render(SDL_Renderer* renderer);
    void renderHUD(SDL_Renderer* renderer);
    void update(float dt, const Uint8* keys, SDL_Renderer* renderer);
    void handleInput(const SDL_Event& event);
};