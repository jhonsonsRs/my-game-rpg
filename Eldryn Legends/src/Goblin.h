#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"

class Goblin : public Entity{
private:
    int goblinDamage;
    float decisionTimer = 0.0f;
    bool andar;
    enum class Direction { RIGHT, LEFT, UP, DOWN};
    Direction currentDirection;
public:
    Goblin(const int x, const int y);
    ~Goblin() override;

    void render(SDL_Renderer* renderer, const SDL_Rect& camera) override;
    void handleEvents(float dt, const Uint8* keys) override;
    void update(float dt) override;
    int getGoblinDamage(){
        return this->goblinDamage;
    }
};
