#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "AnimatedSprite.h"

class HealthPotion {
private:
    SDL_Rect rect;          // Retângulo de posição e colisão
    bool collected;
    AnimatedSprite sprite;
    static const int HEAL_AMOUNT = 20;
    
public:
    HealthPotion(int x, int y, TextureManager* textureManager);
    ~HealthPotion();

    void update(float dt);
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    bool isCollected() const { return collected; }
    void collect() { collected = true; }

    SDL_Rect getRect() const { return rect; }
    int getHealAmount() const { return HEAL_AMOUNT; }
};