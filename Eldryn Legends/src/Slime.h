#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"

class Slime : public Entity{
private:
    float speed = 80;
    int slimeHp = 50;
    int slimeDamage;
public:
    Slime(const int x, const int y);
    ~Slime() override;

    void render(SDL_Renderer* renderer) override;
    void handleEvents(float dt, const Uint8* keys) override;
    void movimentation(float dt);
    int getSlimeDamage(){
        return this->slimeDamage;
    }
};