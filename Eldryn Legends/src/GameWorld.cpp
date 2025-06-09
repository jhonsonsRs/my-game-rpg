#include "GameWorld.h"
#include "GlobalProperties.h"
#include "Map.h"
#include <SDL2/SDL_ttf.h>
#include "Warrior.h"
#include "Goblin.h" 
#include "Camera.h"
#include <memory>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <cmath>
#define _USE_MATH_DEFINES
#include "C:\Games\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

bool colision(float ax, float ay, float aWidth, float aHeight, float bx, float by, float bWidth, float bHeight){
    if( ay + aHeight < by) return false;
    else if(ay > by + bHeight) return false;
    else if(ax + aWidth < bx) return false;
    else if(ax > bx + bWidth) return false;

    return true; 
}

void GameWorld::map(){
    this->mapTerrain1 = new int*[MAP_HEIGHT];
    this->mapTerrain2 = new int*[MAP_HEIGHT];

    for(int i = 0; i < MAP_HEIGHT; i++){
        this->mapTerrain1[i] = new int[MAP_WIDTH];
        std::fill(this->mapTerrain1[i], this->mapTerrain1[i] + MAP_WIDTH, 6);
    }

int fullMap[MAP_HEIGHT][MAP_WIDTH] = {
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,16,17,17,17,17,18,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,16,17,17,17,17,17,17,18,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,16,17,17,17,17,17,17,18,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,30,31,31,31,31,31,31,32,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,30,31,31,31,31,31,31,32,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,37,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,37,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,16,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,10,24,24,24,24,9,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,18,6},
    {6,23,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,25,6},
    {6,23,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,25,6},
    {6,23,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,25,6},
    {6,23,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,25,6},
    {6,30,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,3,24,24,24,24,2,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,32,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,37,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,37,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,16,17,17,17,17,17,17,18,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,16,17,17,17,17,17,17,18,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,24,24,25,6,6,6,6,6,6},
    {6,6,6,6,6,6,30,31,31,31,31,31,31,32,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,30,31,31,31,31,31,31,32,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,23,24,24,24,24,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,30,31,31,31,31,32,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}
};

    // Copia os valores para mapTerrain2
     for(int i = 0; i < MAP_HEIGHT; i++){
        this->mapTerrain2[i] = new int[MAP_WIDTH];
        for(int j = 0; j < MAP_WIDTH; j++){
            this->mapTerrain2[i][j] = fullMap[i][j];
        }
    }
}

GameWorld::GameWorld(SDL_Renderer* renderer, TextureManager* textureManager)
    : camera(), textureManager(textureManager), goblinsKilled(0),
      healthBarTexture(nullptr), healthBarBackgroundTexture(nullptr), 
      gameOver(false), restartTimer(0.0f) {
    this->map();
    this->player = std::make_unique<Warrior>(BASE_WIDTH / 2, BASE_HEIGHT / 2, textureManager);

    spawnRandomGoblins(5);
    spawnRandomPotions(5);
    
    this->gameTerrain1 = std::make_unique<Map>(renderer, "C:/Games/Eldryn Legends/assets/maps/tilesetts.png", this->mapTerrain1, 16, MAP_WIDTH, MAP_WIDTH);
    this->gameTerrain2 = std::make_unique<Map>(renderer, "C:/Games/Eldryn Legends/assets/maps/tilesetts.png", this->mapTerrain2, 16, MAP_WIDTH, MAP_WIDTH);
    
    // Cria texturas para a barra de vida
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 200, 20, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0)); // Vermelho para a vida
    healthBarTexture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 50, 50, 50)); // Cinza para o fundo
    healthBarBackgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void GameWorld::spawnRandomGoblins(int count) {
    static bool seeded = false; // variável que mantém seu valor entre chamadas da função.
    if (!seeded) { 
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    for (int i = 0; i < count; ++i) {
        // Gera posições aleatórias dentro dos limites do mapa (com margem de 100px)
        int x = 100 + (std::rand() % (MAP_WIDTH * 16 - 200));
        int y = 100 + (std::rand() % (MAP_HEIGHT * 16 - 200));
        enemyGoblins.emplace_back(x, y, textureManager);
    }
}

void GameWorld::spawnRandomPotions(int count) {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    for (int i = 0; i < count; ++i) {
        // Spawn potions away from edges (100px margin)
        int x = 100 + (std::rand() % (MAP_WIDTH * 16 - 200));
        int y = 100 + (std::rand() % (MAP_HEIGHT * 16 - 200));
        healthPotions.emplace_back(x, y, textureManager);
    }
}


void GameWorld::render(SDL_Renderer* renderer) {
    // 1. Limpa o renderizador
    SDL_RenderClear(renderer);

    // 2. Salva o viewport original
    SDL_Rect originalViewport;
    SDL_RenderGetViewport(renderer, &originalViewport);

    // 3. Configura o viewport para o mundo do jogo (usando toda a tela)
    SDL_RenderSetViewport(renderer, &originalViewport);
    
    // 4. Obtém a visão da câmera
    SDL_Rect cameraView = this->camera.getView();
    
    // 5. Renderiza os layers do mapa
    this->gameTerrain1->render(renderer, cameraView);
    this->gameTerrain2->render(renderer, cameraView);
    
    // 6. Renderiza os inimigos
    for (auto& goblin : enemyGoblins) {
        if (!goblin.isDead()) {
            goblin.render(renderer, cameraView);
        }
    }
    
    // 7. Renderiza o jogador
    if (!player->isDead()) {  // Só renderiza o jogador se não estiver morto
        this->player->render(renderer, cameraView);
    }

        for (auto& potion : healthPotions) {
        if (!potion.isCollected()) {
            potion.render(renderer, cameraView);
        }
    }

    // 8. Restaura o viewport original para o HUD
    SDL_RenderSetViewport(renderer, &originalViewport);
    
    // 9. Renderiza o HUD (coordenadas absolutas da tela)
    renderHUD(renderer);

    // 10. Atualiza a tela
    SDL_RenderPresent(renderer);
}

void GameWorld::renderHUD(SDL_Renderer* renderer) {
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

    // Barra de vida
    const int healthBarWidth = 100;
    const int healthBarHeight = 10;
    const int margin = 20;
    
    // Fundo da barra de vida
    SDL_Rect healthBarBg = {margin, margin, healthBarWidth, healthBarHeight};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &healthBarBg);

    // Preenchimento da barra de vida (baseado na saúde atual)
    float healthPercentage = static_cast<float>(player->getHealth()) / player->getMaxHealth();
    healthPercentage = std::max(0.0f, std::min(1.0f, healthPercentage)); // Garante entre 0 e 1
    
    SDL_Rect healthBar = {
        margin, 
        margin, 
        static_cast<int>(healthBarWidth * healthPercentage), 
        healthBarHeight
    };
    
    // Mudança de cor baseada na vida (opcional)
    if (healthPercentage > 0.5) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde quando vida > 50%
    } else if (healthPercentage > 0.25) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Amarelo quando vida <= 50%
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Vermelho quando vida <= 25%
    }
    
    SDL_RenderFillRect(renderer, &healthBar);
}

void GameWorld::update(float dt, const Uint8* keys, SDL_Renderer* renderer) {
    if(this->player->isDead()){
        if (!gameOver) {
            gameOver = true;
            restartTimer = 0.0f;
        }
    }

    if(gameOver){
        restartTimer += dt;
        if(restartTimer >= 3.0f){
            restartGame();
        }
        return;  // Não atualiza mais nada enquanto estiver em gameOver
    }
    this->player->update(dt, keys);
    Vector position_player = this->player->getPosition();

    if (enemyGoblins.empty()) {
        spawnRandomGoblins(5); 
    }

    auto it = enemyGoblins.begin();
    while (it != enemyGoblins.end()) {
        if (!it->isDead()) {
            // Check player attack
            if (player->isAttackingNow()) {
                Hitbox* activeHitbox = player->getActiveHitbox();
                if (activeHitbox && !player->hasAlreadyHit()) {
                    if (SDL_HasIntersection(&activeHitbox->getRect(), &it->getRect())) {
                        it->takeDamage(player->getSwordDamage());
                        player->setAlreadyHit(true);
                    }
                }
            }

            // Check collision and determine attack direction
            if (SDL_HasIntersection(&player->getRect(), &it->getRect())) {
                SDL_Rect pRect = player->getRect();
                SDL_Rect gRect = it->getRect();
                
                bool fromTop = (pRect.y + pRect.h) < gRect.y + (gRect.h/3);
                bool fromBottom = pRect.y > gRect.y + (2*gRect.h/3);
                bool fromLeft = (pRect.x + pRect.w) < gRect.x + (gRect.w/3);
                bool fromRight = pRect.x > gRect.x + (2*gRect.w/3);

                if (fromTop) it->activateAttack(Goblin::Direction::UP);
                else if (fromBottom) it->activateAttack(Goblin::Direction::DOWN);
                else if (fromLeft) it->activateAttack(Goblin::Direction::LEFT);
                else if (fromRight) it->activateAttack(Goblin::Direction::RIGHT);
                else it->activateAttack(Goblin::Direction::DOWN);
            }

            // Check goblin attack
            if (it->isAttacking()) {
                Hitbox* goblinHitbox = it->getAttackHitbox();
                if (goblinHitbox && SDL_HasIntersection(&goblinHitbox->getRect(), &player->getRect())) {
                    player->takeDamage(it->getGoblinDamage());
                }
            }
            
            it->update(dt, position_player);
            ++it;
        } else {
            goblinsKilled++; // Incrementa a contagem
            it = enemyGoblins.erase(it);
        }
    }

    auto potionIt = healthPotions.begin();
    while (potionIt != healthPotions.end()) {
        if (!potionIt->isCollected()) {
            SDL_Rect playerRect = player->getRect();
            SDL_Rect potionRect = potionIt->getRect();
            
            if (SDL_HasIntersection(&playerRect, &potionRect)) {
                player->heal(potionIt->getHealAmount());
                potionIt->collect();
                potionIt = healthPotions.erase(potionIt);
                continue;
            }
            
            potionIt->update(dt);
        }
        ++potionIt;
    }

    // Spawn more potions if needed
    if (healthPotions.empty()) {
        spawnRandomPotions(5);
    }

    this->camera.update(
        position_player.x, 
        position_player.y, 
        MAP_WIDTH * 16, 
        MAP_HEIGHT * 16);
}

void GameWorld::restartGame(){
    // Reinicia o jogador
    player->reset();
    
    // Reinicia os inimigos
    enemyGoblins.clear();
    spawnRandomGoblins(3);
    spawnRandomPotions(5);
    
    // Reinicia outros estados
    goblinsKilled = 0;
    gameOver = false;
    restartTimer = 0.0f;
}

void GameWorld::handleInput(const SDL_Event& event){
    this->player->handleEvents(event);
}

GameWorld::~GameWorld(){
    for(int p = 0; p < MAP_HEIGHT; p++){
        delete[] this->mapTerrain1[p];
        delete[] this->mapTerrain2[p];
    }
    delete[] this->mapTerrain1;
    delete[] this->mapTerrain2;
    if (healthBarTexture) SDL_DestroyTexture(healthBarTexture);
    if (healthBarBackgroundTexture) SDL_DestroyTexture(healthBarBackgroundTexture);
}