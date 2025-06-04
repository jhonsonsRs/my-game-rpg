#include "GameManager.h"
#include "GameWorld.h"
#include "GlobalProperties.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "C:\Games\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

float getTime() {
    return static_cast<float>(SDL_GetTicks()) / 1000.0;
}

GameManager::GameManager() : window(nullptr), renderer(nullptr), isRunning(false) {}

SDL_Texture* GameManager::loadTexture(const char* path){
    SDL_Texture* tex = IMG_LoadTexture(renderer, path);
    return tex;
}

bool GameManager::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erro ao inicializar o SDL2: " << SDL_GetError() << std::endl;
        return false;
    }

    this->window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN);

    SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!this->window) {
        std::cerr << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->renderer) {
        std::cerr << "Erro ao criar o renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        return false;
    }

    //warrior
    textureManager.load("warrior_run_right", renderer, "C:/Games/Eldryn Legends/assets/sprites/playerRunRight.png");
    textureManager.load("warrior_run_up", renderer, "C:/Games/Eldryn Legends/assets/sprites/playerRunUp.png");
    textureManager.load("warrior_run_down", renderer, "C:/Games/Eldryn Legends/assets/sprites/playerRunDown.png");
    textureManager.load("warrior_idle_right", renderer, "C:/Games/Eldryn Legends/assets/sprites/playerIdleRight.png");
    textureManager.load("warrior_idle_up", renderer, "C:/Games/Eldryn Legends/assets/sprites/playerIdleUp.png");
    textureManager.load("warrior_idle_down", renderer, "C:/Games/Eldryn Legends/assets/sprites/playerIdleDown.png");
    textureManager.load("warrior_hit_up", renderer, "C:/Games/Eldryn Legends/assets/sprites/playerHitUp.png");
    textureManager.load("warrior_hit_down", renderer, "C:/Games/Eldryn Legends/assets/sprites/playerHitDown.png");
    textureManager.load("warrior_hit_right", renderer, "C:/Games/Eldryn Legends/assets/sprites/playerHitRight.png");

    //player
    textureManager.load("goblin_run_right", renderer, "C:/Games/Eldryn Legends/assets/sprites/goblinRunRight.png");
    textureManager.load("goblin_run_up", renderer, "C:/Games/Eldryn Legends/assets/sprites/goblinRunUp.png");
    textureManager.load("goblin_run_down", renderer, "C:/Games/Eldryn Legends/assets/sprites/goblinRunDown.png");
    textureManager.load("goblin_idle_right", renderer, "C:/Games/Eldryn Legends/assets/sprites/goblinIdleRight.png");
    textureManager.load("goblin_idle_up", renderer, "C:/Games/Eldryn Legends/assets/sprites/goblinIdleUp.png");
    textureManager.load("goblin_idle_down", renderer, "C:/Games/Eldryn Legends/assets/sprites/goblinIdleDown.png");
    textureManager.load("goblin_hit_up", renderer, "C:/Games/Eldryn Legends/assets/sprites/goblinHitUp.png");
    textureManager.load("goblin_hit_down", renderer, "C:/Games/Eldryn Legends/assets/sprites/goblinHitDown.png");
    textureManager.load("goblin_hit_right", renderer, "C:/Games/Eldryn Legends/assets/sprites/goblinHitRight.png");


    SDL_RenderSetLogicalSize(this->renderer, BASE_WIDTH, BASE_HEIGHT);

    this->world = std::make_unique<GameWorld>(this->renderer, &textureManager);
    this->isRunning = true;
    return true;
}

void GameManager::run() {
    float previousTime = getTime();
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    while (this->isRunning) {
        float currentTime = getTime();
        float dt = currentTime - previousTime;
        previousTime = currentTime;

        this->world->update(dt, keys);
        this->render(dt);
        this->handleEvents(dt);
        SDL_Delay(30);
    }
}

void GameManager::handleEvents(float dt) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            this->isRunning = false;
        }
        this->world->handleInput(event);
    }
}

void GameManager::render(float dt) {
    SDL_SetRenderDrawColor(this->renderer, 30, 30, 30, 255);
    SDL_RenderClear(this->renderer);
    this->world->render(this->renderer);
    SDL_RenderPresent(this->renderer);
}

void GameManager::clean() {
    this->world.reset();

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

GameManager::~GameManager() {
    this->clean();
}