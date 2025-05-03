#include <iostream>
#include "Goblin.h"
#include "GlobalProperties.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <random>
#include <cstdlib>
#include <ctime>

Goblin::Goblin(const int x, const int y, SDL_Texture* spriteAtlasRight, SDL_Texture* spriteAtlasUp, SDL_Texture* spriteAtlasDown, SDL_Texture* spriteAtlasRight2, SDL_Texture* spriteAtlasUp2, SDL_Texture* spriteAtlasDown2) :
    Entity(x, y, 30, 50, GOBLIN_WIDTH, GOBLIN_HEIGHT),
    spriteRight(spriteAtlasRight, 16, 16, 4, 0.1f),
    spriteUp(spriteAtlasUp, 16, 16, 4, 0.1f),
    spriteDown(spriteAtlasDown, 16, 16, 4, 0.1f),
    spriteIdleRight(spriteAtlasRight2, 16, 16, 2, 0.5f),
    spriteIdleUp(spriteAtlasUp2, 16, 16, 2, 0.5f),
    spriteIdleDown(spriteAtlasDown2, 16, 16, 2, 0.5f),
    currentDirection(Direction::RIGHT),
    lastDirection(Direction::RIGHT),
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

    if (this->currentDirection == Direction::UP && this->velocity.y == 0) {
        this->spriteIdleUp.render(renderer, renderRect.x, renderRect.y);
    }

    if (this->currentDirection == Direction::DOWN && this->velocity.y == 0) {
        this->spriteIdleDown.render(renderer, renderRect.x, renderRect.y);
    }

    if (this->currentDirection == Direction::LEFT && this->velocity.x == 0) {
        this->spriteIdleRight.render(renderer, renderRect.x, renderRect.y, SDL_FLIP_HORIZONTAL);
    }

    if (this->currentDirection == Direction::RIGHT && this->velocity.x == 0) {
        this->spriteIdleRight.render(renderer, renderRect.x, renderRect.y);
    }

    // A sprite do player andando só vai ser desenhada se o x ou y da velocidade for diferente de 0
    if (this->currentDirection == Direction::RIGHT && this->velocity.x != 0) {
        this->spriteRight.render(renderer, renderRect.x, renderRect.y);
    }

    if (this->currentDirection == Direction::LEFT && this->velocity.x != 0) {
        this->spriteRight.render(renderer, renderRect.x, renderRect.y, SDL_FLIP_HORIZONTAL);
    }

    if (this->currentDirection == Direction::UP && this->velocity.y != 0) {
        this->spriteUp.render(renderer, renderRect.x, renderRect.y);
    }

    if (this->currentDirection == Direction::DOWN && this->velocity.y != 0) {
        this->spriteDown.render(renderer, renderRect.x, renderRect.y);
    }
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
                this->lastDirection = Direction::UP;
                this->velocity.y = -this->speed;
                break;
            case 2:
                this->andar = true;
                this->currentDirection = Direction::DOWN;
                this->lastDirection = Direction::DOWN;
                this->velocity.y = this->speed;
                break;
            case 3:
                this->andar = true;
                this->currentDirection = Direction::RIGHT;
                this->lastDirection = Direction::RIGHT;
                this->velocity.x = this->speed;
                break;
            case 4:
                this->andar = true;
                this->currentDirection = Direction::LEFT;
                this->lastDirection = Direction::LEFT;
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

    if (this->currentDirection == Direction::UP && this->velocity.y == 0) {
        this->spriteIdleUp.update(dt);
    }

    if (this->currentDirection == Direction::DOWN && this->velocity.y == 0) {
        this->spriteIdleDown.update(dt);
    }

    if (this->currentDirection == Direction::LEFT && this->velocity.x == 0) {
        this->spriteIdleRight.update(dt);
    }

    if (this->currentDirection == Direction::RIGHT && this->velocity.x == 0) {
        this->spriteIdleRight.update(dt);
    }

    switch (this->currentDirection) {
    case Direction::RIGHT:
        this->spriteRight.update(dt);
        break;
    case Direction::LEFT:
        this->spriteRight.update(dt);
        break;
    case Direction::UP:
        this->spriteUp.update(dt);
        break;
    case Direction::DOWN:
        this->spriteDown.update(dt);
        break;
    }
}
