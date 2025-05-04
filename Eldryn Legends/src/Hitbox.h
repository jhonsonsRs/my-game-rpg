#pragma once
#include <SDL2/SDL.h>
#include "C:\Games\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

class Hitbox{
private:
    SDL_Rect rect;
    Vector position;
public:
    Hitbox(const int x, const int y, const int w, const int h);
    ~Hitbox();

    void render(SDL_Renderer* renderer, const SDL_Rect& camera);
    void setHitboxPosition(int newX, int newY);

    Vector getHitboxPosition() const {
        return this->position;
    }
};