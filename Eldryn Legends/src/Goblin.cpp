#include <iostream>
#include "Goblin.h"
#include "GlobalProperties.h"
#include "Hitbox.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <random>
#include <cstdlib>
#include <ctime>

Goblin::Goblin(const int x, const int y, TextureManager* textureManager) :
    Entity(x, y, 30, 50, GOBLIN_WIDTH, GOBLIN_HEIGHT),
    hitboxTop(0, 0, HITBOX_SIZE, HITBOX_SIZE),     
    hitboxBottom(0, 0, HITBOX_SIZE, HITBOX_SIZE),  
    hitboxRight(0, 0, HITBOX_SIZE, HITBOX_SIZE),   
    hitboxLeft(0, 0, HITBOX_SIZE, HITBOX_SIZE), 
    spriteRight(textureManager->get("goblin_run_right"), 16, 16, 4, 0.1f, true),
    spriteUp(textureManager->get("goblin_run_up"), 16, 16, 4, 0.1f, true),
    spriteDown(textureManager->get("goblin_run_down"), 16, 16, 4, 0.1f, true),
    spriteIdleRight(textureManager->get("goblin_idle_right"), 16, 16, 2, 0.5f, true),
    spriteIdleUp(textureManager->get("goblin_idle_up"), 16, 16, 2, 0.5f, true),
    spriteIdleDown(textureManager->get("goblin_idle_down"), 16, 16, 2, 0.5f, true),
    spriteHitUp(textureManager->get("goblin_hit_up"), 16, 16, 4, 0.1f, false),
    spriteHitDown(textureManager->get("goblin_hit_down"), 16, 19, 4, 0.1f, false),
    spriteHitRight(textureManager->get("goblin_hit_right"), 16, 16, 4, 0.1f, false),
    currentDirection(Direction::RIGHT),
    lastDirection(Direction::RIGHT),
    dead(false),
    attacking(false),
    attackCooldown(2.0f),
    timeSinceLastAttack(0.0f),
    attackDuration(0.5f),
    currentAttackTime(0.0f),
    hitboxTopActive(false),
    hitboxBottomActive(false),
    hitboxLeftActive(false),
    hitboxRightActive(false),
    goblinDamage(30) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Goblin::~Goblin(){}

void Goblin::handleEvents(const SDL_Event& event){}

void Goblin::render(SDL_Renderer* renderer, const SDL_Rect& camera){
    if(this->dead) return;
    SDL_Rect renderRect;
    renderRect.x = this->rect.x - camera.x;
    renderRect.y = this->rect.y - camera.y;
    renderRect.w = this->rect.w;
    renderRect.h = this->rect.h;

    if(this->attacking){
        switch (this->lastDirection) {
            case Direction::UP:
                this->spriteHitUp.render(renderer, renderRect.x, renderRect.y);
                break;
            case Direction::DOWN:
                this->spriteHitDown.render(renderer, renderRect.x, renderRect.y);
                break;
            case Direction::LEFT:
                this->spriteHitRight.render(renderer, renderRect.x, renderRect.y, SDL_FLIP_HORIZONTAL);
                break;
            case Direction::RIGHT:
                this->spriteHitRight.render(renderer, renderRect.x, renderRect.y);
                break;
        }
    } else {
        if (this->currentDirection == Direction::UP && this->velocity.y == 0) {
            this->spriteIdleUp.render(renderer, renderRect.x, renderRect.y);
        } else if (this->currentDirection == Direction::DOWN && this->velocity.y == 0) {
            this->spriteIdleDown.render(renderer, renderRect.x, renderRect.y);
        } else if (this->currentDirection == Direction::LEFT && this->velocity.x == 0) {
            this->spriteIdleRight.render(renderer, renderRect.x, renderRect.y, SDL_FLIP_HORIZONTAL);
        } else if (this->currentDirection == Direction::RIGHT && this->velocity.x == 0) {
            this->spriteIdleRight.render(renderer, renderRect.x, renderRect.y);
        }

        if (this->currentDirection == Direction::RIGHT && this->velocity.x != 0) {
            this->spriteRight.render(renderer, renderRect.x, renderRect.y);
        } else if (this->currentDirection == Direction::LEFT && this->velocity.x != 0) {
            this->spriteRight.render(renderer, renderRect.x, renderRect.y, SDL_FLIP_HORIZONTAL);
        } else if (this->currentDirection == Direction::UP && this->velocity.y != 0) {
            this->spriteUp.render(renderer, renderRect.x, renderRect.y);
        } else if (this->currentDirection == Direction::DOWN && this->velocity.y != 0) {
            this->spriteDown.render(renderer, renderRect.x, renderRect.y);
        }
    }
}

void Goblin::update(float dt, const Uint8* keys){
    if(this->dead) return;

    this->timeSinceLastAttack += dt;

    if(!this->attacking){
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
                    this->velocity.y = -this->speed * (0.5f + (std::rand() % 100)/100.0f);
                    break;
                case 2:
                    this->andar = true;
                    this->currentDirection = Direction::DOWN;
                    this->lastDirection = Direction::DOWN;
                    this->velocity.y = this->speed * (0.5f + (std::rand() % 100)/100.0f);
                    break;
                case 3:
                    this->andar = true;
                    this->currentDirection = Direction::RIGHT;
                    this->lastDirection = Direction::RIGHT;
                    this->velocity.x = this->speed * (0.5f + (std::rand() % 100)/100.0f); 
                    break;
                case 4:
                    this->andar = true;
                    this->currentDirection = Direction::LEFT;
                    this->lastDirection = Direction::LEFT;
                    this->velocity.x = -this->speed * (0.5f + (std::rand() % 100)/100.0f);
                    break;
            }

            this->decisionTimer = 2.0f;
        }

        if(this->andar){
            this->position += this->velocity * dt;
            this->rect.x = static_cast<int>(this->position.x);
            this->rect.y = static_cast<int>(this->position.y);
        }
    }

    if(this->attacking) {
        this->handleAttack(dt);
    } else {
        if (this->currentDirection == Direction::UP && this->velocity.y == 0) {
            this->spriteIdleUp.update(dt);
        } else if (this->currentDirection == Direction::DOWN && this->velocity.y == 0) {
            this->spriteIdleDown.update(dt);
        } else if (this->currentDirection == Direction::LEFT && this->velocity.x == 0) {
            this->spriteIdleRight.update(dt);
        } else if (this->currentDirection == Direction::RIGHT && this->velocity.x == 0) {
            this->spriteIdleRight.update(dt);
        }
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

    this->updateHitbox();
}

void Goblin::handleAttack(float dt){
    this->currentAttackTime += dt;
    switch(this->lastDirection){
        case Direction::UP:
            this->spriteHitUp.update(dt);
            break;
        case Direction::DOWN:
            this->spriteHitDown.update(dt);
            break;
        case Direction::LEFT:
            this->spriteHitRight.update(dt);
            break;
        case Direction::RIGHT:
            this->spriteHitRight.update(dt);
            break;
    }

    if(this->currentAttackTime >= this->attackDuration / 2 &&
    !(this->hitboxTopActive || this->hitboxBottomActive || this->hitboxRightActive || this->hitboxLeftActive)){
        this->activateAttackHitbox();
    }

    if (this->currentAttackTime >= this->attackDuration) {
        this->attacking = false;
        this->hitboxTopActive = false;
        this->hitboxBottomActive = false;
        this->hitboxRightActive = false;
        this->hitboxLeftActive = false;
        this->timeSinceLastAttack = 0.0f;
        
        this->spriteHitUp.reset();
        this->spriteHitDown.reset();
        this->spriteHitRight.reset();
    }
}

void Goblin::activateAttackHitbox(){
    this->hitboxTopActive = false;
    this->hitboxBottomActive = false;
    this->hitboxRightActive = false;
    this->hitboxLeftActive = false;

    switch (this->lastDirection) {
        case Direction::UP:
            this->hitboxTopActive = true;
            break;
        case Direction::DOWN:
            this->hitboxBottomActive = true;
            break;
        case Direction::LEFT:
            this->hitboxLeftActive = true;
            break;
        case Direction::RIGHT:
            this->hitboxRightActive = true;
            break;
    }
}

void Goblin::activateAttack(Direction direction){
    if (!this->attacking && this->timeSinceLastAttack >= this->attackCooldown) {
        this->attacking = true;
        this->lastDirection = direction;
        this->currentAttackTime = 0.0f;

        this->velocity.x = 0;
        this->velocity.y = 0;

        switch(direction){
            case Direction::UP:
                this->spriteHitUp.reset();
                break;
            case Direction::DOWN:
                this->spriteHitDown.reset();
                break;
            case Direction::LEFT:
                this->spriteHitRight.reset();
                break;
            case Direction::RIGHT:
                this->spriteHitRight.reset();
                break;
        }
    }
}

void Goblin::updateHitbox(){
    this->hitboxTop.setHitboxPosition(this->position.x, this->position.y - (GOBLIN_HEIGHT + 2));
    this->hitboxBottom.setHitboxPosition(this->position.x, this->position.y + (GOBLIN_HEIGHT + 2));
    this->hitboxRight.setHitboxPosition(this->position.x + (GOBLIN_WIDTH + 2), this->position.y);
    this->hitboxLeft.setHitboxPosition(this->position.x - (GOBLIN_WIDTH + 2), this->position.y);
}   

void Goblin::takeDamage(int damage){
    this->hp -= damage;
    if(this->hp <= 0){
        this->dead = true;
    }
}

bool Goblin::isDead() const{
    return this->dead;
}

bool Goblin::isAttacking() const{
    return this->attacking;
}

Hitbox* Goblin::getAttackHitbox() {
    if (this->hitboxTopActive) return &this->hitboxTop;
    if (this->hitboxBottomActive) return &this->hitboxBottom;
    if (this->hitboxRightActive) return &this->hitboxRight;
    if (this->hitboxLeftActive) return &this->hitboxLeft;
    return nullptr;
}

Hitbox* Goblin::getHitboxTop() { return &this->hitboxTop; }
Hitbox* Goblin::getHitboxBottom() { return &this->hitboxBottom; }
Hitbox* Goblin::getHitboxRight() { return &this->hitboxRight; }
Hitbox* Goblin::getHitboxLeft() { return &this->hitboxLeft; }

SDL_Rect& Goblin::getRect() {
    return this->rect; 
}

const SDL_Rect& Goblin::getRect() const {
    return this->rect;
}