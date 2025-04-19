#include <iostream>
#include "Warrior.h"
#include "GlobalProperties.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

const int warriorHeight = 64;
const int warriorWidth = 64;

Warrior::Warrior(const int x, const int y, SDL_Texture* spriteAtlasRight, SDL_Texture* spriteAtlasUp, SDL_Texture* spriteAtlasDown, SDL_Texture* spriteAtlasRight2, SDL_Texture* spriteAtlasUp2, SDL_Texture* spriteAtlasDown2) : 
    Entity(x, y, 50, 100, PLAYER_WIDTH, PLAYER_HEIGHT),
    spriteRight(spriteAtlasRight, 16, 16, 4, 0.1f),
    spriteUp(spriteAtlasUp, 16, 16, 4, 0.1f),
    spriteDown(spriteAtlasDown, 16, 16, 4, 0.1f),
    spriteIdleRight(spriteAtlasRight2, 16, 16, 2, 0.1f),
    spriteIdleUp(spriteAtlasUp2, 16, 16, 2, 0.1f),
    spriteIdleDown(spriteAtlasDown2, 16, 16, 2, 0.1f),
    currentDirection(Direction::RIGHT),
    lastDirection(Direction::RIGHT),
    swordDamage(20){}

Warrior::~Warrior() {
}

void Warrior::handleEvents(float dt, const Uint8* keys){
    if(keys[SDL_SCANCODE_W]){
        this->velocity.y = -this->speed;
        this->currentDirection = Direction::UP;
        this->lastDirection = Direction::UP;
    } else if(keys[SDL_SCANCODE_S]) {
        this->velocity.y = this->speed;
        this->currentDirection = Direction::DOWN;
        this->lastDirection = Direction::DOWN;
    } else {
        this->velocity.y = 0;
    }

    if(keys[SDL_SCANCODE_A]){
        this->velocity.x = -this->speed;
        this->currentDirection = Direction::LEFT;
        this->lastDirection = Direction::LEFT;
    } else if(keys[SDL_SCANCODE_D]){
        this->velocity.x = this->speed;
        this->currentDirection = Direction::RIGHT;
        this->lastDirection = Direction::RIGHT;
    } else {
        this->velocity.x = 0;
    }

    if(velocity.x == 0 || velocity.y == 0){
        idle = true;
    }

    this->position += this->velocity * dt;
    this->rect.x = static_cast<int>(position.x);
    this->rect.y = static_cast<int>(position.y);
}

void Warrior::update(float dt){
    
    if(currentDirection == Direction::UP && velocity.y == 0){
        //std::cout << "parado para cima" << std::endl;
        spriteIdleUp.update(dt);
    }

    if(currentDirection == Direction::DOWN && velocity.y == 0){
        //std::cout << "parado para baixo" << std::endl;
        spriteIdleDown.update(dt);
    }

    if(currentDirection == Direction::LEFT && velocity.x == 0){
        //std::cout << "parado para esquerda" << std::endl;
        spriteIdleRight.update(dt);
    }

    if(currentDirection == Direction::RIGHT && velocity.x == 0){
        //std::cout << "parado para direita" << std::endl;
        spriteIdleRight.update(dt);
    }

    switch(currentDirection){
        case Direction::RIGHT:
            spriteRight.update(dt);
        break;
        case Direction::LEFT:
            spriteRight.update(dt);
        break;
        case Direction::UP:
            spriteUp.update(dt);
        break;
        case Direction::DOWN:
            spriteDown.update(dt);
        break;
    }
}

void Warrior::render(SDL_Renderer* renderer, const SDL_Rect& camera){
    SDL_Rect renderRect;
    renderRect.x = rect.x - camera.x;
    renderRect.y = rect.y - camera.y;
    renderRect.w = rect.w;
    renderRect.h = rect.h;


    //a sprite do player parado só vai ser desenhado se o x ou y da velocidade for 0
    if(currentDirection == Direction::UP && velocity.y == 0){
      spriteIdleUp.render(renderer, renderRect.x, renderRect.y);
    }

    if(currentDirection == Direction::DOWN && velocity.y == 0){
        spriteIdleDown.render(renderer, renderRect.x, renderRect.y);
    }

    if(currentDirection == Direction::LEFT && velocity.x == 0){
        spriteIdleRight.render(renderer, renderRect.x, renderRect.y, SDL_FLIP_HORIZONTAL);
    }

    if(currentDirection == Direction::RIGHT && velocity.x == 0){
        spriteIdleRight.render(renderer, renderRect.x, renderRect.y);
    }



    //A sprite do player andando só vai ser desehada se o x ou y da velocidade for diferente de 0
    if(currentDirection == Direction::RIGHT && velocity.x != 0){
        spriteRight.render(renderer, renderRect.x, renderRect.y);
    }

    if(currentDirection == Direction::LEFT && velocity.x != 0){
        spriteRight.render(renderer, renderRect.x, renderRect.y, SDL_FLIP_HORIZONTAL);
    }

    if(currentDirection == Direction::UP && velocity.y != 0){
        spriteUp.render(renderer, renderRect.x, renderRect.y);
    }

    if(currentDirection == Direction::DOWN && velocity.y != 0){
        spriteDown.render(renderer, renderRect.x, renderRect.y);
    }
}
