#pragma once
#include <SDL2/SDL.h>
#include "Entity.h"

class Warrior : public Entity{
private:
    float speed = 120;
    int warriorHp = 100;
    int swordDamage;
public:
    Warrior(const int x, const int y);
    ~Warrior() override;

    void render(SDL_Renderer* renderer) override;
    void handleEvents(float dt, const Uint8* keys) override;
    
    int getSwordDamage(){
        return this->swordDamage;
    }
};