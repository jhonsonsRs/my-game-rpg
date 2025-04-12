#include <iostream>
#include "Slime.h"
#include <SDL2/SDL.h>
#include <random>
#include <cstdlib>
#include <ctime>

const int slimeHeight = 32;
const int slimeWidth = 32;

Slime::Slime(const int x, const int y) :
    Entity(x, y, speed, slimeHp, slimeWidth, slimeHeight),
    slimeDamage(5) {}

Slime::~Slime(){}

void Slime::handleEvents(float dt, const Uint8* keys){}

void Slime::render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Slime::movimentation(float dt){
    int choice = rand()%2;
    switch(choice){
        case 0:

        break;
        case 1:
        
        break;
        case 2:

        break;
    }
}