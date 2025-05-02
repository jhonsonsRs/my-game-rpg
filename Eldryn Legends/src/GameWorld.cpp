#include "GameWorld.h"
#include "GlobalProperties.h"
#include "Map.h"
#include "Warrior.h"
#include "Goblin.h"  // Alterado de Wolf para Goblin
#include "Camera.h"
#include <memory>
#include <iostream>
#include <SDL2/SDL_image.h>
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

    for(int i = 0; i < MAP_HEIGHT; i++){
        this->mapTerrain2[i] = new int[MAP_WIDTH] {
            -1, -1, -1, -1, -1, -1, -1, -1, 5, 5, 5, 5, 5, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1, -1, 8, -1, -1, -1, 5, 5, 7, 5, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, 5, 5, 5, 5, -1, -1, -1, -1, -1, -1, -1
        };
    }
}

GameWorld::GameWorld(SDL_Renderer* renderer, 
    SDL_Texture* spriteAtlasRight, 
    SDL_Texture* spriteAtlasUp, 
    SDL_Texture* spriteAtlasDown, 
    SDL_Texture* spriteAtlasRight2, 
    SDL_Texture* spriteAtlasUp2, 
    SDL_Texture* spriteAtlasDown2) : camera() {
    this->map();
    this->player = std::make_unique<Warrior>(BASE_WIDTH / 2, BASE_HEIGHT / 2, spriteAtlasRight, spriteAtlasUp, spriteAtlasDown, spriteAtlasRight2, spriteAtlasUp2, spriteAtlasDown2);
    this->enemyGoblin = std::make_unique<Goblin>(BASE_WIDTH / 2, BASE_HEIGHT / 2);  // Alterado para Goblin
    
    this->gameTerrain1 = std::make_unique<Map>(renderer, "C:/Users/Usuario/OneDrive/Área de Trabalho/Jogo C++/Eldryn Legends/assets/maps/tilesetts.png", this->mapTerrain1, 16, MAP_WIDTH, MAP_WIDTH);
    this->gameTerrain2 = std::make_unique<Map>(renderer, "C:/Users/Usuario/OneDrive/Área de Trabalho/Jogo C++/Eldryn Legends/assets/maps/tilesetts.png", this->mapTerrain2, 16, MAP_WIDTH, MAP_WIDTH);
}

GameWorld::~GameWorld(){
    for(int p = 0; p < MAP_HEIGHT; p++){
        delete[] this->mapTerrain1[p];
        delete[] this->mapTerrain2[p];
    }
    delete[] this->mapTerrain1;
    delete[] this->mapTerrain2;
}

void GameWorld::render(SDL_Renderer* renderer){
    this->gameTerrain1->render(renderer, this->camera.getView());
    this->gameTerrain2->render(renderer, this->camera.getView());
    this->player->render(renderer, this->camera.getView());
    this->enemyGoblin->render(renderer, this->camera.getView());  // Alterado para Goblin
}

void GameWorld::update(float dt){
    this->player->update(dt);
    this->enemyGoblin->update(dt);  // Alterado para Goblin

    Vector position_goblin = this->enemyGoblin->getPosition();  // Alterado para Goblin
    Vector position_player = this->player->getPosition();

    if(colision(position_goblin.x, position_goblin.y, GOBLIN_WIDTH, GOBLIN_HEIGHT, position_player.x, position_player.y, PLAYER_WIDTH, PLAYER_HEIGHT)){
        std::cout << "tocou" << std::endl;
    }

    this->camera.update(
        position_player.x, 
        position_player.y, 
        MAP_WIDTH * 16, 
        MAP_HEIGHT * 16);
}

void GameWorld::handleInput(float dt, const Uint8* keys){
    this->player->handleEvents(dt, keys);
}
