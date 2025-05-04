#include <iostream>
#include "Warrior.h"
#include "GlobalProperties.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

const int warriorHeight = 64;
const int warriorWidth = 64;

Warrior::Warrior(const int x, const int y, SDL_Texture* spriteAtlasRight, 
    SDL_Texture* spriteAtlasUp, 
    SDL_Texture* spriteAtlasDown, 
    SDL_Texture* spriteAtlasRight2, 
    SDL_Texture* spriteAtlasUp2, 
    SDL_Texture* spriteAtlasDown2,
    SDL_Texture* spriteAtlasHitUp,
    SDL_Texture* spriteAtlasHitDown,
    SDL_Texture* spriteAtlasHitRight) :

    Entity(x, y, 50, 100, PLAYER_WIDTH, PLAYER_HEIGHT),
    hitboxTop(0, 0, HITBOX_SIZE, HITBOX_SIZE),     
    hitboxBottom(0, 0, HITBOX_SIZE, HITBOX_SIZE),  
    hitboxRight(0, 0, HITBOX_SIZE, HITBOX_SIZE),   
    hitboxLeft(0, 0, HITBOX_SIZE, HITBOX_SIZE), 
    spriteRight(spriteAtlasRight, 16, 16, 4, 0.1f, true),
    spriteUp(spriteAtlasUp, 16, 16, 4, 0.1f, true),
    spriteDown(spriteAtlasDown, 16, 16, 4, 0.1f, true),
    spriteIdleRight(spriteAtlasRight2, 16, 16, 2, 0.5f, true),
    spriteIdleUp(spriteAtlasUp2, 16, 16, 2, 0.5f, true),
    spriteIdleDown(spriteAtlasDown2, 16, 16, 2, 0.5f, true),
    spriteHitUp(spriteAtlasHitUp, 16, 16, 4, 0.1f, false),
    spriteHitDown(spriteAtlasHitDown, 16, 19, 4, 0.1f, false),
    spriteHitRight(spriteAtlasHitRight, 16, 16, 4, 0.1f, false),
    currentDirection(Direction::RIGHT),
    lastDirection(Direction::RIGHT),
    swordDamage(20) {}

Warrior::~Warrior() {
}

void Warrior::handleEvents(const SDL_Event& event) {
    if(event.type == SDL_MOUSEBUTTONDOWN){
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        if(event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_RIGHT ){
            isAttacking = true;
            spriteHitUp.reset();
            spriteHitDown.reset();
            spriteHitRight.reset();
        }
    }
}

void Warrior::update(float dt, const Uint8* keys) {
    if(isAttacking){
        velocity.x = 0;
        velocity.y = 0;
    } else {
        if (keys[SDL_SCANCODE_W]) {
            this->velocity.y = -this->speed; 
            this->currentDirection = Direction::UP;
            this->lastDirection = Direction::UP;
        }
        else if (keys[SDL_SCANCODE_S]) {
            this->velocity.y = this->speed;
            this->currentDirection = Direction::DOWN;
            this->lastDirection = Direction::DOWN;
        }
        else {
            this->velocity.y = 0;
        }

        if (keys[SDL_SCANCODE_A]) {
            this->velocity.x = -this->speed;
            this->currentDirection = Direction::LEFT;
            this->lastDirection = Direction::LEFT;
        }
        else if (keys[SDL_SCANCODE_D]) {
            this->velocity.x = this->speed;
            this->currentDirection = Direction::RIGHT;
            this->lastDirection = Direction::RIGHT;
        }
        else {
            this->velocity.x = 0;
        }
    }
    if (this->velocity.x == 0 || this->velocity.y == 0) {
        this->idle = true;
    } else {
        idle = false;
    }

    this->position += this->velocity * dt;
    this->rect.x = static_cast<int>(this->position.x);
    this->rect.y = static_cast<int>(this->position.y);


    if(isAttacking){
        //UPDATE HIT
        if(this->lastDirection == Direction::UP){
            this->spriteHitUp.update(dt);
            if(this->spriteHitUp.isLastFrame()){
                isAttacking = false;    
            }
        }

        else if(this->lastDirection == Direction::DOWN){
            this->spriteHitDown.update(dt);
            if(this->spriteHitDown.isLastFrame()){
                isAttacking = false;
            }
        }

        else if(this->lastDirection == Direction::RIGHT){
            this->spriteHitRight.update(dt);
            if(this->spriteHitRight.isLastFrame()){
                isAttacking = false;
            }
        }

        else if(this->lastDirection == Direction::LEFT){
            this->spriteHitRight.update(dt);
            if(this->spriteHitRight.isLastFrame()){
                isAttacking = false;
            }
        }
    }
    

    //UPDATE IDLE
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

    //UPDATE RUN
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

    updateHitbox();
}

void Warrior::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    SDL_Rect renderRect;
    renderRect.x = this->rect.x - camera.x;
    renderRect.y = this->rect.y - camera.y;
    renderRect.w = this->rect.w;
    renderRect.h = this->rect.h;

    if(isAttacking){
        //RENDER SPRITE HIT
        if(this->lastDirection == Direction::UP){
            this->spriteHitUp.render(renderer, renderRect.x, renderRect.y);
        }

        if(this->lastDirection == Direction::DOWN){
            this->spriteHitDown.render(renderer, renderRect.x, renderRect.y);
        }

        if(this->lastDirection == Direction::RIGHT){
            this->spriteHitRight.render(renderer, renderRect.x, renderRect.y);
        }

        if(this->lastDirection == Direction::LEFT){
            this->spriteHitRight.render(renderer, renderRect.x, renderRect.y, SDL_FLIP_HORIZONTAL);
        }
    } else {
        // A sprite do player parado só vai ser desenhada se o x ou y da velocidade for 0
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
    hitboxTop.render(renderer, camera);
    hitboxBottom.render(renderer, camera);
    hitboxRight.render(renderer, camera);
    hitboxLeft.render(renderer, camera);
}

void Warrior::updateHitbox(){

    hitboxTop.setHitboxPosition(position.x, position.y - (PLAYER_HEIGHT + 2));
    hitboxBottom.setHitboxPosition(position.x, position.y + (PLAYER_HEIGHT + 2));
    hitboxRight.setHitboxPosition(position.x + (PLAYER_WIDTH + 2), position.y);
    hitboxLeft.setHitboxPosition(position.x - (PLAYER_WIDTH + 2), position.y);
    
}   