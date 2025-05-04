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

    //Hitbox
    Hitbox hitboxTop;
    Hitbox hitboxBottom;
    Hitbox hitboxRight;
    Hitbox hitboxLeft;

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
    void updateHitbox() override;
    
    int getSwordDamage(){
        return this->swordDamage;
    }
};