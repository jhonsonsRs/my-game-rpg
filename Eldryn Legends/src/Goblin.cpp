#include <iostream>
#include "Goblin.h"
#include "GlobalProperties.h"
#include <SDL2/SDL.h>
#include <random>
#include <cstdlib>
#include <ctime>

Goblin::Goblin(const int x, const int y) :
    Entity(x, y, 30, 50, GOBLIN_WIDTH, GOBLIN_HEIGHT),
    currentDirection(Direction::RIGHT),
    goblinDamage(5) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Goblin::~Goblin(){}

void Goblin::handleEvents(float dt, const Uint8* keys){}

void Goblin::render(SDL_Renderer* renderer, const SDL_Rect& camera){
    SDL_Rect renderRect;
    renderRect.x = this->rect.x - camera.x;
    renderRect.y = this->rect.y - camera.y;
    renderRect.w = this->rect.w;
    renderRect.h = this->rect.h;
    SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255);
    SDL_RenderFillRect(renderer, &renderRect);
}

void Goblin::update(float dt){
    this->decisionTimer -= dt;

    if(this->decisionTimer <= 0.0f){
        int choice = std::rand() % 5;
        this->velocity = {0, 0};
        this->andar = false;

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

    if(this->andar){
        this->position += this->velocity * dt;
        this->rect.x = static_cast<int>(this->position.x);
        this->rect.y = static_cast<int>(this->position.y);
    }
}
