#include "World.h"
#include <iostream>

World::World(int width, int height) : mapRect{0, 0, width, height} {}
World::~World(){
    SDL_DestroyTexture(backgroundTexture);
}

void World::loadMap(SDL_Renderer* renderer, const char* path){
    SDL_Surface* tempSurface = IMG_Load(path);
    if(!tempSurface){
        std::cerr << "Erro ao carregar o mapa: " <<   IMG_GetError() << std::endl;
        return false;
    }

    mapTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if(!mapTexture){
        std::cerr << "Erro ao criar a textura do mapa: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void World::update(float dt){
    for(auto& e : entities){
        e->handleEvents(dt, nullptr);
    }
}

void World::render(SDL_Renderer* renderer, SDL_Rect camera){
    SDL_RenderCopy(renderer, mapTexture, &camera, nullptr);
    for (auto& e : entities) {
        static_cast<int>(entidade->getPosition().x - camera.x),  
        static_cast<int>(entidade->getPosition().y - camera.y),  
        entidade->getRect().w,  
        entidade->getRect().h  
    };
    entidade->render(renderer);  
}

void World::addEntity(Entity* entities){
    entities.push_back(entities);
}