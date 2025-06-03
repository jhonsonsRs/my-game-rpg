#include "AnimatedSprite.h"
#include <SDL2/SDL_image.h>
#include <iostream>

AnimatedSprite::AnimatedSprite(SDL_Texture* spriteAtlas, int frameWidth, int frameHeight, int frameCount, float frameDuration, bool loop)
    : spriteAtlas(spriteAtlas), 
    frameWidth(frameWidth), 
    frameHeight(frameHeight),
    frameCount(frameCount), 
    frameDuration(frameDuration), 
    loop(loop),
    currentFrame(0), 
    elapsedTime(0.0f)
{

    frames.reserve(frameCount); //otimização de memória

    for (int i = 0; i < this->frameCount; i++) {
        SDL_Rect frameRect = { i * this->frameWidth, 0, this->frameWidth, this->frameHeight };
        this->frames.push_back(frameRect);
    }
}

void AnimatedSprite::update(float dt){
    this->elapsedTime += dt;
    if (this->elapsedTime >= this->frameDuration) {
        this->currentFrame++;
        this->elapsedTime = 0.0f;

        if (this->currentFrame >= this->frameCount) {
            if (this->loop) {
                this->currentFrame = 0;
            } else {
                this->currentFrame = this->frameCount - 1;
            }
        }
    }
}

void AnimatedSprite::render(SDL_Renderer* renderer, int x, int y, SDL_RendererFlip flip){
    SDL_Rect currentFrameRect = this->frames[this->currentFrame];
    SDL_Rect destRect = { x, y, this->frameWidth, this->frameHeight };
    SDL_RenderCopyEx(renderer, this->spriteAtlas, &currentFrameRect, &destRect, 0.0, nullptr, flip);
}

void AnimatedSprite::reset(){
    this->currentFrame = 0;
    this->elapsedTime = 0.0f;
}

bool AnimatedSprite::isLastFrame() const {
    return !loop && currentFrame == frameCount - 1;
}