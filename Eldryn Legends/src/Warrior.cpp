#include <iostream>
#include "Warrior.h"
#include "GlobalProperties.h"
#include <SDL2/SDL.h>

const int warriorHeight = 64;
const int warriorWidth = 64;

Warrior::Warrior(const int x, const int y) : 
    Entity(x, y, 50, 100, PLAYER_WIDTH, PLAYER_HEIGHT),
    swordDamage(20) {}

Warrior::~Warrior() {
}

void Warrior::handleEvents(float dt, const Uint8* keys){
    if(keys[SDL_SCANCODE_W]){
        this->velocity.y = -this->speed;
    } else if(keys[SDL_SCANCODE_S]) {
        this->velocity.y = this->speed;
    } else {
        this->velocity.y = 0;
    }

    if(keys[SDL_SCANCODE_A]){
        this->velocity.x = -this->speed;
    } else if(keys[SDL_SCANCODE_D]){
        this->velocity.x = this->speed;
    } else {
        this->velocity.x = 0;
    }

    this->position += this->velocity * dt;
    this->rect.x = static_cast<int>(position.x);
    this->rect.y = static_cast<int>(position.y);
}

void Warrior::render(SDL_Renderer* renderer, const SDL_Rect& camera){
    SDL_Rect renderRect;
    renderRect.x = rect.x - camera.x;
    renderRect.y = rect.y - camera.y;
    renderRect.w = rect.w;
    renderRect.h = rect.h;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &renderRect);
}
