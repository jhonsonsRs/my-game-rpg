#include "GameWorld.h"
#include "GlobalProperties.h"
#include "Map.h"
#include "Warrior.h"
#include "Slime.h"
#include "Camera.h"
#include <memory>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "C:\Users\Usuario\OneDrive\Área de Trabalho\Jogo C++\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

bool colision(float ax, float ay, float aWidth, float aHeight, float bx, float by, float bWidth, float bHeight){
    if( ay+ aHeight < by) return false;
    else if(ay > by + bHeight) return false;
    else if(ax + aWidth < bx) return false;
    else if(ax > bx + bWidth) return false;

    return true; 
}

void GameWorld::map(){
    mapTerrain1 = new int*[MAP_HEIGHT];
    mapTerrain2 = new int*[MAP_HEIGHT];

    for(int i = 0; i < MAP_HEIGHT; i++){
        mapTerrain1[i] = new int[MAP_WIDTH]{
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
        };
    }

    for(int i = 0; i < MAP_HEIGHT; i++){
        mapTerrain2[i] = new int[MAP_WIDTH] {
            -1, -1, -1, -1, -1, -1, -1, -1, 5, 5, 5, 5, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, 5, 7, 5, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, 5, 5, 5, 5, -1, -1, -1, -1, -1, -1, -1
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
    map();
    player = std::make_unique<Warrior>(BASE_WIDTH / 2, BASE_HEIGHT / 2, spriteAtlasRight, spriteAtlasUp, spriteAtlasDown, spriteAtlasRight2, spriteAtlasUp2, spriteAtlasDown2);
    enemySlime = std::make_unique<Slime>(BASE_WIDTH / 2, BASE_HEIGHT / 2);
    gameTerrain1 = std::make_unique<Map>(renderer, "C:/Users/Usuario/OneDrive/Área de Trabalho/Jogo C++/Eldryn Legends/assets/maps/tilesets.png", mapTerrain1, 16, MAP_WIDTH, MAP_HEIGHT);
    gameTerrain2 = std::make_unique<Map>(renderer, "C:/Users/Usuario/OneDrive/Área de Trabalho/Jogo C++/Eldryn Legends/assets/maps/tilesets.png", mapTerrain2, 16, MAP_WIDTH, MAP_HEIGHT);

}

GameWorld::~GameWorld(){
    for(int p = 0; p < MAP_HEIGHT; p++){
        delete[] mapTerrain1[p];
        delete[] mapTerrain2[p];
    }
    delete[] mapTerrain1;
    delete[] mapTerrain2;
}

void GameWorld::render(SDL_Renderer* renderer){
    gameTerrain1->render(renderer, camera.getView());
    gameTerrain2->render(renderer, camera.getView());
    player->render(renderer, camera.getView());
    enemySlime->render(renderer, camera.getView());
}

void GameWorld::update(float dt){
    player->update(dt);
    enemySlime->update(dt);

    Vector position_slime = enemySlime->getPosition();
    Vector position_player = player->getPosition();

    if(colision(position_slime.x, position_slime.y, SLIME_WIDTH, SLIME_HEIGHT, position_player.x, position_player.y, PLAYER_WIDTH, PLAYER_HEIGHT)){
        std::cout<< "tocou" << std::endl;

    }
                                                        //MAP_WIDTH * tilesize, MAP_HEIGHT * tilesize
    camera.update(
        position_player.x, 
        position_player.y, 
        MAP_WIDTH * 16, 
        MAP_HEIGHT * 16);
}

void GameWorld::handleInput(float dt, const Uint8* keys){
    player->handleEvents(dt, keys);
}
