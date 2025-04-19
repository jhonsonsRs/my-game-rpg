#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"

class Slime : public Entity{
private:
    int slimeDamage;
    float decisionTimer = 0.0f;
    bool andar;
    enum class Direction { RIGHT, LEFT, UP, DOWN};
    Direction currentDirection;
public:
    Slime(const int x, const int y);
    ~Slime() override;

    void render(SDL_Renderer* renderer, const SDL_Rect& camera) override;
    void handleEvents(float dt, const Uint8* keys) override;
    void movimentation(float dt);
    int getSlimeDamage(){
        return this->slimeDamage;
    }
};