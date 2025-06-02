#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"
#include "AnimatedSprite.h"
#include "Hitbox.h"

class Goblin : public Entity{
public:
    enum class Direction { RIGHT, LEFT, UP, DOWN};
private:
    int goblinDamage;
    float decisionTimer = 0.0f;
    bool andar;
    bool dead;

    Hitbox hitboxTop;
    Hitbox hitboxBottom;
    Hitbox hitboxRight;
    Hitbox hitboxLeft;

    bool hitboxTopActive = false;
    bool hitboxBottomActive = false;
    bool hitboxRightActive = false;
    bool hitboxLeftActive = false;

    bool alreadyHit = false;
    bool attacking;
    float attackCooldown;
    float timeSinceLastAttack;
    float attackDuration;
    float currentAttackTime;


    AnimatedSprite spriteUp;
    AnimatedSprite spriteDown;
    AnimatedSprite spriteRight;
    AnimatedSprite spriteIdleUp;
    AnimatedSprite spriteIdleDown;
    AnimatedSprite spriteIdleRight;

    AnimatedSprite spriteHitUp;
    AnimatedSprite spriteHitDown;
    AnimatedSprite spriteHitRight;

    Direction currentDirection;
    Direction lastDirection;
public:
    Goblin(const int x, const int y, SDL_Texture* spriteAtlasRight, 
        SDL_Texture* spriteAtlasUp, 
        SDL_Texture* spriteAtlasDown, 
        SDL_Texture* spriteAtlasRight2, 
        SDL_Texture* spriteAtlasUp2, 
        SDL_Texture* spriteAtlasDown2,
        SDL_Texture* spriteAtlasHitUp,
        SDL_Texture* spriteAtlasHitDown,
        SDL_Texture* spriteAtlasHitRight);
    ~Goblin() override;

    void render(SDL_Renderer* renderer, const SDL_Rect& camera) override;
    void handleEvents(const SDL_Event& event) override;
    void update(float dt, const Uint8* keys) override;
    void updateHitbox() override;
    void takeDamage(int damage);
    bool isDead() const;

    void handleAttack(float dt);
    void activateAttack(Direction direction);
    void activateAttackHitbox();
    bool isAttacking() const;
    Hitbox* getAttackHitbox();

    SDL_Rect& getRect();
    const SDL_Rect& getRect() const;

    int getGoblinDamage(){
        return this->goblinDamage;
    }

    Hitbox* getHitboxTop();
    Hitbox* getHitboxBottom();
    Hitbox* getHitboxRight();
    Hitbox* getHitboxLeft();

    Direction getAttackDirection() const {
        return lastDirection;
    }
};