#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"
#include "AnimatedSprite.h"

class Warrior : public Entity{
private:
    int swordDamage;
    bool idle = false;
    AnimatedSprite spriteUp;
    AnimatedSprite spriteDown;
    AnimatedSprite spriteRight;
    AnimatedSprite spriteIdleUp;
    AnimatedSprite spriteIdleDown;
    AnimatedSprite spriteIdleRight;
    enum class Direction { RIGHT, LEFT, UP, DOWN};
    Direction currentDirection;
    Direction lastDirection;
public:
    Warrior(const int x, const int y, SDL_Texture* spriteAtlasRight, SDL_Texture* spriteAtlasUp, SDL_Texture* spriteAtlasDown, SDL_Texture* spriteAtlasRight2, SDL_Texture* spriteAtlasUp2, SDL_Texture* spriteAtlasDown2);
    ~Warrior() override;

    void update(float dt) override;
    void render(SDL_Renderer* renderer, const SDL_Rect& camera) override;
    void handleEvents(float dt, const Uint8* keys) override;
    
    int getSwordDamage(){
        return this->swordDamage;
    }
};