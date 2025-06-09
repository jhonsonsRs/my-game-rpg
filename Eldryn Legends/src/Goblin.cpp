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

void Goblin::update(float dt, const Uint8* keys){}

void Goblin::update(float dt, const Vector& playerPosition) {
    if (dead) return;

    this->timeSinceLastAttack += dt;

    Vector goblinPosition = getPosition();
    float dist = distance(goblinPosition, playerPosition);

    if (attacking) {
        handleAttack(dt);
        updateHitbox();
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        return;
    }

    if (position.x < 0) {
        position.x = 0;
        velocity.x = speed; 
        currentDirection = Direction::RIGHT;
    } 
    else if (position.x > SCREEN_WIDTH - GOBLIN_WIDTH) {
        position.x = SCREEN_WIDTH - GOBLIN_WIDTH;
        velocity.x = -speed; 
        currentDirection = Direction::LEFT;
    }

    if (position.y < 0) {
        position.y = 0;
        velocity.y = speed;
        currentDirection = Direction::DOWN;
    } 
    else if (position.y > SCREEN_HEIGHT - GOBLIN_HEIGHT) {
        position.y = SCREEN_HEIGHT - GOBLIN_HEIGHT;
        velocity.y = -speed;
        currentDirection = Direction::UP;
    }

    //segue o player
    if (dist < GOBLIN_DETECTION_RADIUS) {
        Vector direction = playerPosition - goblinPosition;
        if (direction.length() > 0.0001f) {
            direction.normalize();
            velocity = direction * speed;

            if (std::abs(velocity.x) > std::abs(velocity.y)) {
                currentDirection = (velocity.x > 0) ? Direction::RIGHT : Direction::LEFT;
            } else {
                currentDirection = (velocity.y > 0) ? Direction::DOWN : Direction::UP;
            }
        } else {
            velocity = {0, 0};
        }
    //se não anda normal
    } else {
        decisionTimer -= dt;
        if (decisionTimer <= 0.0f) {
            int choice = std::rand() % 5;
            velocity = {0, 0};
            andar = false;

            switch (choice) {
                case 1:
                    andar = true;
                    velocity.y = -speed;
                    currentDirection = Direction::UP;
                    break;
                case 2:
                    andar = true;
                    velocity.y = speed;
                    currentDirection = Direction::DOWN;
                    break;
                case 3:
                    andar = true;
                    velocity.x = speed;
                    currentDirection = Direction::RIGHT;
                    break;
                case 4:
                    andar = true;
                    velocity.x = -speed;
                    currentDirection = Direction::LEFT;
                    break;
                default:
                    andar = false;
                    break;
            }
            decisionTimer = 2.0f;
        }
    }

    if (andar || dist < GOBLIN_DETECTION_RADIUS) {
        position += velocity * dt;
    }

    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);

    // Animation updates remain the same...
    if (velocity.x == 0 && velocity.y == 0) {
        switch (currentDirection) {
            case Direction::UP: spriteIdleUp.update(dt); break;
            case Direction::DOWN: spriteIdleDown.update(dt); break;
            case Direction::LEFT: spriteIdleRight.update(dt); break;
            case Direction::RIGHT: spriteIdleRight.update(dt); break;
        }
    } else {
        switch (currentDirection) {
            case Direction::RIGHT:
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

    updateHitbox();
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

float Goblin::distance(const Vector& a, const Vector& b){
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
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