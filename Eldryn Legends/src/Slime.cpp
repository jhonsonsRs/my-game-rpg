#include <iostream>
#include "Slime.h"
#include <SDL2/SDL.h>
#include <random>
#include <cstdlib>
#include <ctime>

const int slimeHeight = 32;
const int slimeWidth = 32;

Slime::Slime(const int x, const int y) :
    Entity(x, y, 80, 50, slimeWidth, slimeHeight),
    currentDirection(Direction::RIGHT),
    slimeDamage(5) {}

Slime::~Slime(){}

void Slime::handleEvents(float dt, const Uint8* keys){}

void Slime::render(SDL_Renderer* renderer, const SDL_Rect& camera){
    SDL_Rect renderRect;
    renderRect.x = rect.x - camera.x;
    renderRect.y = rect.y - camera.y;
    renderRect.w = rect.w;
    renderRect.h = rect.h;
    SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255);
    SDL_RenderFillRect(renderer, &renderRect);
}

void Slime::update(float dt){
    this->decisionTimer -= dt;

    if(this->decisionTimer <= 0.0f){
        int choice = rand()%5;
        this->velocity = {0, 0};

        switch(choice){
            case 0:
                this->velocity.x = 0;
                this->velocity.y = 0;
                this->andar = false;
            break;
            case 1:
                this->andar = true;
                this->currentDirection = Direction::UP;
                this->velocity.y = -this->speed;
            break;
            case 2:
                this->andar = true;
                this->currentDirection = Direction::DOWN;
                this->velocity.y = this->speed;
            break;
            case 3:
                this->andar = true;
                this->currentDirection = Direction::RIGHT;
                this->velocity.x = this->speed;
            break;
            case 4:
                this->andar = true;
                this->currentDirection = Direction::LEFT;
                this->velocity.x = -this->speed;
            break;
        }

        this->decisionTimer = 5.0f;
    }

    if(andar){
        this->position += this->velocity * dt;
        this->rect.x = static_cast<int>(position.x);
        this->rect.y = static_cast<int>(position.y);
    }
    
}