#pragma once
#include <SDL2/SDL.h>
#include "C:\Games\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

class Entity{
protected:
    Vector position;
    Vector velocity;
    float speed;
    int hp;
    SDL_Rect rect;
public:
    Entity(const int x, const int y, float speed, int hp, int w, int h) : position(x, y), velocity(0,0), hp(hp), speed(speed) {
        this->rect = {static_cast<int>(position.x), static_cast<int>(position.y), w, h};
    }

    virtual ~Entity() = default;

    virtual void update(float dt, const Uint8* keys) = 0;
    virtual void render(SDL_Renderer* renderer, const SDL_Rect& camera) = 0;
    virtual void handleEvents(const SDL_Event& event) = 0;
    virtual void updateHitbox() = 0;

    Vector getPosition() const {
        return this->position;
    }
};