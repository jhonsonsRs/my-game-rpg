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
    mapData = new int*[MAP_HEIGHT];
    /*for(int i = 0; i < MAP_HEIGHT; i++){
        mapData[i] = new int[MAP_WIDTH] {
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6
        };
    }*/
    mapData[0] = new int[MAP_WIDTH]{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    mapData[1] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[2] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[3] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[4] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[5] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[6] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[7] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[8] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[9] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[10] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[11] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[12] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[13] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[14] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[15] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[16] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[17] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[18] = new int[MAP_WIDTH]{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    mapData[19] = new int[MAP_WIDTH]{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
}

GameWorld::GameWorld(SDL_Renderer* renderer) : camera(){
    map();
    player = std::make_unique<Warrior>(BASE_WIDTH / 2, BASE_HEIGHT / 2);
    enemySlime = std::make_unique<Slime>(BASE_WIDTH / 2, BASE_HEIGHT / 2);
    gameMap = std::make_unique<Map>(renderer, "C:/Users/Usuario/OneDrive/Área de Trabalho/Jogo C++/Eldryn Legends/assets/maps/tilesets.png", mapData, 16, MAP_WIDTH, MAP_HEIGHT);

}

GameWorld::~GameWorld(){
    for(int p = 0; p < MAP_HEIGHT; p++){
        delete[] mapData[p];
    }
    delete[] mapData;
}

void GameWorld::render(SDL_Renderer* renderer){
    gameMap->render(renderer, camera.getView());
    player->render(renderer, camera.getView());
    enemySlime->render(renderer, camera.getView());
}

void GameWorld::update(float dt){
    enemySlime->movimentation(dt);

    Vector position_slime = enemySlime->getPosition();
    Vector position_player = player->getPosition();

    if(colision(position_slime.x, position_slime.y, 32, 32, position_player.x, position_player.y, 64, 64)){
        std::cout<< "tocou" << std::endl;

    }
                                                        //MAP_WIDTH * tilesize, MAP_HEIGHT * tilesize
    camera.update(
        position_player.x, 
        position_player.y, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT);
}

void GameWorld::handleInput(float dt, const Uint8* keys){
    player->handleEvents(dt, keys);
}
