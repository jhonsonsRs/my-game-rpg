#include <iostream>
#include "Hitbox.h"
#include <SDL2/SDL.h>
#include "C:\Games\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

Hitbox::Hitbox(const int x, const int y, const int w, const int h) : position(x, y){
    this->rect = {static_cast<int>(position.x), static_cast<int>(position.y), w, h};
}

void Hitbox::render(SDL_Renderer* renderer, const SDL_Rect& camera){
    SDL_Rect renderRect;
    renderRect.x = this->rect.x - camera.x;
    renderRect.y = this->rect.y - camera.y;
    renderRect.w = this->rect.w;
    renderRect.h = this->rect.h;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100); 
    SDL_RenderDrawRect(renderer, &renderRect);
    SDL_RenderFillRect(renderer, &renderRect);
}

void Hitbox::setHitboxPosition(int newX, int newY){
    position.x = newX;
    position.y = newY;    
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
}

void Hitbox::setActive(bool isActive){
    active = isActive;
}

bool Hitbox::isActive() const {
    return active;
}

SDL_Rect& Hitbox::getRect() {
    return rect; // Supondo que você tenha um membro SDL_Rect rect;
}

const SDL_Rect& Hitbox::getRect() const {
    return rect;
}

Hitbox::~Hitbox(){}