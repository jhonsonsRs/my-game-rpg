#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "TextureManager.h"

class GameWorld;
class TextureManager;

class GameManager{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    TextureManager textureManager;

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
