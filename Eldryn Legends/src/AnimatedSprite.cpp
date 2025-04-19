#include "AnimatedSprite.h"
#include <SDL2/SDL_image.h>
#include <iostream>

AnimatedSprite::AnimatedSprite(SDL_Texture* spriteAtlas, int frameWidth, int frameHeight, int frameCount, float frameDuration, bool loop)
    : spriteAtlas(spriteAtlas), frameWidth(frameWidth), frameHeight(frameHeight),
      frameCount(frameCount), frameDuration(frameDuration), loop(loop),
      currentFrame(0), elapsedTime(0.0f)
{
    for (int i = 0; i < this->frameCount; i++) {
        SDL_Rect frameRect = { i * this->frameWidth, 0, this->frameWidth, this->frameHeight };
        frames.push_back(frameRect);
    }
}
AnimatedSprite::~AnimatedSprite(){}

void AnimatedSprite::update(float dt){
    this->elapsedTime += dt;
        if(this->elapsedTime >= this->frameDuration){ //se elapsedTime é maior ou igual a duração do frame, passa para o próximo frame
            this->currentFrame++;
            this->elapsedTime = 0.0f; //reseta o tempo

            if(this->currentFrame >= this->frameCount){ //se o próximo frame ultrapassar o total de frames
                if(loop){   //se for um loop, a animação recomeça e a contagem vai pra 0 (primeiro frame)
                    this->currentFrame = 0;
                } else {    //se não, para a animação, com a contagem sendo o ultimo
                    this->currentFrame = this->frameCount - 1;  
                }
            }
        }
}

void AnimatedSprite::render(SDL_Renderer* renderer, int x, int y, SDL_RendererFlip flip){
    SDL_Rect currentFrameRect = frames[currentFrame];   //define o retângulo em que será desenhado, basicamente para pegar o sprite da spriteAtlas
    SDL_Rect destRect = {x, y, frameWidth, frameHeight};    //define a posição que será desenhado
    SDL_RenderCopyEx(renderer, spriteAtlas, &currentFrameRect, &destRect, 0.0, nullptr, flip);    //copia a area da spriteAtlas(currentFrameRect), e cola na posição da tela (destRect)
}

void AnimatedSprite::reset(){
    this->currentFrame = 0;
    this->elapsedTime = 0.0f;
}