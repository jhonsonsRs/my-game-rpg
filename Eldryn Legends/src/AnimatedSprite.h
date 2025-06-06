#pragma once
#include <SDL2/SDL.h>
#include <vector>

class AnimatedSprite{
private:    
    SDL_Texture* spriteAtlas = nullptr;
    int frameWidth;
    int frameHeight;
    int frameCount; 
    float frameDuration;
    bool loop;
    int currentFrame;
    float elapsedTime;
    std::vector<SDL_Rect> frames;
public:
    AnimatedSprite(SDL_Texture* spriteAtlas, int framWidth, int framHeight, int frameCount, float frameDuration, bool loop);
    ~AnimatedSprite() = default;

    void update(float dt);
    void render(SDL_Renderer* renderer, int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void reset();
    bool isLastFrame() const;
};