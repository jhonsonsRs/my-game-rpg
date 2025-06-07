#include <iostream>
#include "Warrior.h"
#include "GlobalProperties.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

const int warriorHeight = 64;
const int warriorWidth = 64;

Warrior::Warrior(const int x, const int y, TextureManager* textureManager) :

    Entity(x, y, 50, hp, PLAYER_WIDTH, PLAYER_HEIGHT),
    hitboxTop(0, 0, HITBOX_SIZE, HITBOX_SIZE),     
    hitboxBottom(0, 0, HITBOX_SIZE, HITBOX_SIZE),  
    hitboxRight(0, 0, HITBOX_SIZE, HITBOX_SIZE),   
    hitboxLeft(0, 0, HITBOX_SIZE, HITBOX_SIZE), 
    spriteRight(textureManager->get("warrior_run_right"), 16, 16, 4, 0.1f, true),
    spriteUp(textureManager->get("warrior_run_up"), 16, 16, 4, 0.1f, true),
    spriteDown(textureManager->get("warrior_run_down"), 16, 16, 4, 0.1f, true),
    spriteIdleRight(textureManager->get("warrior_idle_right"), 16, 16, 2, 0.5f, true),
    spriteIdleUp(textureManager->get("warrior_idle_up"), 16, 16, 2, 0.5f, true),
    spriteIdleDown(textureManager->get("warrior_idle_down"), 16, 16, 2, 0.5f, true),
    spriteHitUp(textureManager->get("warrior_hit_up"), 16, 16, 4, 0.1f, false),
    spriteHitDown(textureManager->get("warrior_hit_down"), 16, 19, 4, 0.1f, false),
    spriteHitRight(textureManager->get("warrior_hit_right"), 16, 16, 4, 0.1f, false),
    currentDirection(Direction::RIGHT),
    lastDirection(Direction::RIGHT),
    invencible(false),
    invencibilityTimer(0.0f),
    blinkTimer(0.0f),
    isVisible(true),
    swordDamage(20) {}

Warrior::~Warrior() {
}

void Warrior::handleEvents(const SDL_Event& event) {
    if(event.type == SDL_MOUSEBUTTONDOWN){
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        if(event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_RIGHT ){
            this->isAttacking = true;
            this->spriteHitUp.reset();
            this->spriteHitDown.reset();
            this->spriteHitRight.reset();

            this->hitboxTopActive = false;
            this->hitboxBottomActive = false;
            this->hitboxRightActive = false;
            this->hitboxLeftActive = false;

            this->activateAttackHitbox();

            if(this->lastDirection == Direction::RIGHT){
                this->hitboxRightActive = true;
            } else if(this->lastDirection == Direction::LEFT){
                this->hitboxLeftActive = true;
            } else if(this->lastDirection == Direction::UP){
                this->hitboxTopActive = true;
            } else if(this->lastDirection == Direction::DOWN){
                this->hitboxBottomActive = true;
            }
        }
    }
}

void Warrior::update(float dt, const Uint8* keys) {
    if(this->invencible){
        this->invencibilityTimer += dt;
        this->blinkTimer +=  dt;

        if(this->blinkTimer >= 0.1f) {
            this->isVisible = !this->isVisible;
            this->blinkTimer = 0.0f;
        }

        if(this->invencibilityTimer >= INVINCIBILITY_DURATION){
            this->invencible = false;
            this->isVisible = true;
        }
    }

    if(this->isAttacking){
        this->velocity.x = 0;
        this->velocity.y = 0;
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
        this->idle = false;
    }

    this->position += this->velocity * dt;
    this->rect.x = static_cast<int>(this->position.x);
    this->rect.y = static_cast<int>(this->position.y);

    if(this->isAttacking){
        if(this->lastDirection == Direction::UP){
            this->spriteHitUp.update(dt);
            if(this->spriteHitUp.isLastFrame()){
                this->isAttacking = false;    
                this->alreadyHit = false;
                this->hitboxTopActive = false;
            }
        }
        else if(this->lastDirection == Direction::DOWN){
            this->spriteHitDown.update(dt);
            if(this->spriteHitDown.isLastFrame()){
                this->isAttacking = false;
                this->alreadyHit = false;
                this->hitboxBottomActive = false;
            }
        }
        else if(this->lastDirection == Direction::RIGHT){
            this->spriteHitRight.update(dt);
            if(this->spriteHitRight.isLastFrame()){
                this->isAttacking = false;
                this->alreadyHit = false;
                this->hitboxRightActive = false;
            }
        }
        else if(this->lastDirection == Direction::LEFT){
            this->spriteHitRight.update(dt);
            if(this->spriteHitRight.isLastFrame()){
                this->isAttacking = false;
                this->alreadyHit = false;
                this->hitboxLeftActive = false;
            }
        }
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

    this->updateHitbox();
}

void Warrior::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    if(!this->isVisible) return;
    SDL_Rect renderRect;
    renderRect.x = this->rect.x - camera.x;
    renderRect.y = this->rect.y - camera.y;
    renderRect.w = this->rect.w;
    renderRect.h = this->rect.h;

    if(this->isAttacking){
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
}

void Warrior::activateAttackHitbox(){
    this->hitboxTop.setActive(false);
    this->hitboxBottom.setActive(false);
    this->hitboxLeft.setActive(false);
    this->hitboxRight.setActive(false);

    switch (this->lastDirection) {
        case Direction::UP:
            this->hitboxTop.setActive(true);
            break;
        case Direction::DOWN:
            this->hitboxBottom.setActive(true);
            break;
        case Direction::LEFT:
            this->hitboxLeft.setActive(true);
            break;
        case Direction::RIGHT:
            this->hitboxRight.setActive(true);
            break;
    }
}

void Warrior::updateHitbox(){
    this->hitboxTop.setHitboxPosition(this->position.x, this->position.y - (PLAYER_HEIGHT + 2));
    this->hitboxBottom.setHitboxPosition(this->position.x, this->position.y + (PLAYER_HEIGHT + 2));
    this->hitboxRight.setHitboxPosition(this->position.x + (PLAYER_WIDTH + 2), this->position.y);
    this->hitboxLeft.setHitboxPosition(this->position.x - (PLAYER_WIDTH + 2), this->position.y);
}   

void Warrior::reset(){
    hp = maxHp;
    dead = false;
    position = Vector(BASE_WIDTH / 2, BASE_HEIGHT / 2);
}

void Warrior::takeDamage(int damage){
    if(!this->invencible) {
        this->hp -= damage;
        if(this->hp <= 0) {
            this->dead = true;
            this->hp = 0;
        }

        this->invencible = true;
        this->invencibilityTimer = 0.0f; // Reset the timer
        this->blinkTimer = 0.0f;
        this->isVisible = true;
    }
}

void Warrior::heal(int amount){
    hp += amount;
    if(this->hp > maxHp){
        this->hp = maxHp;
    }
}

bool Warrior::isInvencible() const{
    return this->invencible;
}

Hitbox* Warrior::getHitboxTop() {
    return &this->hitboxTop;
}

Hitbox* Warrior::getHitboxBottom() {
    return &this->hitboxBottom;
}

Hitbox* Warrior::getHitboxRight() {
    return &this->hitboxRight;
}

Hitbox* Warrior::getHitboxLeft() {
    return &this->hitboxLeft;
}

void Warrior::startAttack() {
    this->isAttacking = true;
}

void Warrior::stopAttack() {
    this->isAttacking = false;
    this->alreadyHit = false;
}

bool Warrior::isAttackingNow() const {
    return this->isAttacking;
}

bool Warrior::hasAlreadyHit() const {
    return this->alreadyHit;
}

void Warrior::setAlreadyHit(bool value) {
    this->alreadyHit = value;
}

Hitbox* Warrior::getActiveHitbox() const {
    if (this->hitboxTopActive) return const_cast<Hitbox*>(&this->hitboxTop);
    if (this->hitboxBottomActive) return const_cast<Hitbox*>(&this->hitboxBottom);
    if (this->hitboxRightActive) return const_cast<Hitbox*>(&this->hitboxRight);
    if (this->hitboxLeftActive) return const_cast<Hitbox*>(&this->hitboxLeft);
    return nullptr;
}

SDL_Rect& Warrior::getRect() {
    return this->rect; 
}

const SDL_Rect& Warrior::getRect() const {
    return this->rect;
}