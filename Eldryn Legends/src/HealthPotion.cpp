#include "HealthPotion.h"

HealthPotion::HealthPotion(int x, int y, TextureManager* textureManager) 
    : collected(false),
      sprite(textureManager->get("health_potion"), 16, 16, 1, 0.2f, true) {
    // Inicializa o retângulo de posição/colisão
    rect.x = x;
    rect.y = y;
    rect.w = 16;  // Largura da poção
    rect.h = 16;  // Altura da poção
}

HealthPotion::~HealthPotion() {}

void HealthPotion::update(float dt) {
    if (!collected) {
        sprite.update(dt);
    }
}

void HealthPotion::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    if (!collected) {
        SDL_Rect renderRect = {
            rect.x - camera.x,
            rect.y - camera.y,
            rect.w,
            rect.h
        };
        sprite.render(renderer, renderRect.x, renderRect.y);
    }
}