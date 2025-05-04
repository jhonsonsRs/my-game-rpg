#pragma once
#include <SDL2/SDL.h>
#include <memory>

class GameWorld;

class GameManager{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    SDL_Texture* warriorRightTexture;
    SDL_Texture* warriorUpTexture;
    SDL_Texture* warriorDownTexture;
    SDL_Texture* warriorIdleUpTexture;
    SDL_Texture* warriorIdleRightTexture;
    SDL_Texture* warriorIdleDownTexture;
    SDL_Texture* warriorHitUpTexture;
    SDL_Texture* warriorHitDownTexture;
    SDL_Texture* warriorHitRightTexture;

    SDL_Texture* goblinRightTexture;
    SDL_Texture* goblinUpTexture;
    SDL_Texture* goblinDownTexture;
    SDL_Texture* goblinIdleUpTexture;
    SDL_Texture* goblinIdleRightTexture;
    SDL_Texture* goblinIdleDownTexture;

    std::unique_ptr<GameWorld> world;
public:
    GameManager();
    ~GameManager();

    bool init(const char* title, int width, int height);
    void handleEvents(float dt);
    void render(float dt);
    void clean();
    void run();
};
