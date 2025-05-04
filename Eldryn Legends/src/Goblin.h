#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"
#include "AnimatedSprite.h"
#include "Hitbox.h"

class Goblin : public Entity{
private:
    int goblinDamage;
    float decisionTimer = 0.0f;
    bool andar;
    bool dead;

    Hitbox hitboxTop;
    Hitbox hitboxBottom;
    Hitbox hitboxRight;
    Hitbox hitboxLeft;

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
    Goblin(const int x, const int y, SDL_Texture* spriteAtlasRight, SDL_Texture* spriteAtlasUp, SDL_Texture* spriteAtlasDown, SDL_Texture* spriteAtlasRight2, SDL_Texture* spriteAtlasUp2, SDL_Texture* spriteAtlasDown2);
    ~Goblin() override;

    void render(SDL_Renderer* renderer, const SDL_Rect& camera) override;
    void handleEvents(const SDL_Event& event) override;
    void update(float dt, const Uint8* keys) override;
    void updateHitbox() override;
    void takeDamage(int damage);
    bool isDead() const;

    int getGoblinDamage(){
        return this->goblinDamage;
    }
};
