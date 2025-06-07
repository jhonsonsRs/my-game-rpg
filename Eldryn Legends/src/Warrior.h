#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"
#include "AnimatedSprite.h"
#include "TextureManager.h"
#include "Hitbox.h"

class Warrior : public Entity{
private:
    int swordDamage;
    bool idle = false;
    bool isAttacking = false;
    bool invencible;
    bool dead = false;
    float invencibilityTimer;
    int hp = 100;
    int maxHp = 100;
    const float INVINCIBILITY_DURATION = 0.5f;
    bool isVisible = true;
    const float BLINK_INTERVAL = 0.1f; // Pisca a cada 0.1 segundos
    float blinkTimer = 0.0f;

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

    TextureManager* textureManager;

    enum class Direction { RIGHT, LEFT, UP, DOWN};
    Direction currentDirection;
    Direction lastDirection;
public:
    Warrior(const int x, const int y, TextureManager* textureManager);
    ~Warrior() override;

    void update(float dt, const Uint8* keys) override;
    void render(SDL_Renderer* renderer, const SDL_Rect& camera) override;
    void handleEvents(const SDL_Event& event) override;

    int getHealth() const { return hp; }
    int getMaxHealth() const { return maxHp; }
    bool isDead() const { return dead; }
    void reset();
    void heal(int amount);


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