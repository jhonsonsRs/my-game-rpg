#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"
#include "AnimatedSprite.h"
#include "Hitbox.h"

class Warrior : public Entity{
private:
    int swordDamage;
    bool idle = false;
    bool isAttacking = false;
    bool invencible;
    bool dead = false;
    float invencibilityTimer;
    const float INVINCIBILITY_DURATION = 0.5f;

    //Hitbox
    Hitbox hitboxTop;
    Hitbox hitboxBottom;
    Hitbox hitboxRight;
    Hitbox hitboxLeft;

    bool hitboxTopActive = false;
    bool hitboxBottomActive = false;
    bool hitboxRightActive = false;
    bool hitboxLeftActive = false;
    bool alreadyHit = false;

    //Hit
    AnimatedSprite spriteHitUp;
    AnimatedSprite spriteHitDown;
    AnimatedSprite spriteHitRight;

    //Run
    AnimatedSprite spriteUp;
    AnimatedSprite spriteDown;
    AnimatedSprite spriteRight;

    //Idle
    AnimatedSprite spriteIdleUp;
    AnimatedSprite spriteIdleDown;
    AnimatedSprite spriteIdleRight;

    enum class Direction { RIGHT, LEFT, UP, DOWN};
    Direction currentDirection;
    Direction lastDirection;
public:
    Warrior(const int x, const int y, SDL_Texture* spriteAtlasRight, 
        SDL_Texture* spriteAtlasUp, 
        SDL_Texture* spriteAtlasDown, 
        SDL_Texture* spriteAtlasRight2, 
        SDL_Texture* spriteAtlasUp2, 
        SDL_Texture* spriteAtlasDown2,
        SDL_Texture* spriteAtlasHitUp,
        SDL_Texture* spriteAtlasHitDown,
        SDL_Texture* spriteAtlasHitRight);
    ~Warrior() override;

    void update(float dt, const Uint8* keys) override;
    void render(SDL_Renderer* renderer, const SDL_Rect& camera) override;
    void handleEvents(const SDL_Event& event) override;

    void startAttack();
    void stopAttack();    
    bool isAttackingNow() const;
    bool hasAlreadyHit() const;
    void setAlreadyHit(bool value);

    Hitbox* getActiveHitbox() const;
    void activateAttackHitbox();
    void updateHitbox() override;
    void takeDamage(int damage);
    bool isInvencible() const;

    Hitbox* getHitboxTop();
    Hitbox* getHitboxBottom();
    Hitbox* getHitboxRight();
    Hitbox* getHitboxLeft();
    
    SDL_Rect& getRect();
    const SDL_Rect& getRect() const;

    int getSwordDamage(){
        return this->swordDamage;
    }
};