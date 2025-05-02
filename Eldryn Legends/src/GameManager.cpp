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

bool GameManager::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erro ao inicializar o SDL2: " << SDL_GetError() << std::endl;
        return -1;
    }

    this->window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN);

    // Tela cheia
    SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!this->window) {
        std::cerr << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->renderer) {
        std::cerr << "Erro ao criar o renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(this->renderer);
        SDL_Quit();
        return false;
    }

    this->warriorRightTexture = IMG_LoadTexture(this->renderer, "C:/Games/Eldryn Legends/assets/sprites/playerRunRight.png");
    this->warriorUpTexture = IMG_LoadTexture(this->renderer, "C:/Games/Eldryn Legends/assets/sprites/playerRunUp.png");
    this->warriorDownTexture = IMG_LoadTexture(this->renderer, "C:/Games/Eldryn Legends/assets/sprites/playerRunDown.png");
    this->warriorIdleRightTexture = IMG_LoadTexture(this->renderer, "C:/Games/Eldryn Legends/assets/sprites/playerIdleRight.png");
    this->warriorIdleUpTexture = IMG_LoadTexture(this->renderer, "C:/Games/Eldryn Legends/assets/sprites/playerIdleUp.png");
    this->warriorIdleDownTexture = IMG_LoadTexture(this->renderer, "C:/Games/Eldryn Legends/assets/sprites/playerIdleDown.png");

    if (!this->warriorRightTexture || !this->warriorUpTexture || !this->warriorDownTexture || !this->warriorIdleDownTexture || !this->warriorIdleRightTexture || !this->warriorIdleUpTexture) {
        std::cerr << "Erro ao carregar as spritesheets do jogador: " << IMG_GetError() << std::endl;
        return -1;
    }

    SDL_RenderSetLogicalSize(this->renderer, BASE_WIDTH, BASE_HEIGHT);

    this->world = std::make_unique<GameWorld>(
        this->renderer,
        this->warriorRightTexture,
        this->warriorUpTexture,
        this->warriorDownTexture,
        this->warriorIdleRightTexture,
        this->warriorIdleUpTexture,
        this->warriorIdleDownTexture
    );
    this->isRunning = true;
    return true;
}

void GameManager::run() {
    float previousTime = getTime();
    while (this->isRunning) {
        float currentTime = getTime();
        float dt = currentTime - previousTime;
        previousTime = currentTime;

        this->world->update(dt);
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
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    this->world->handleInput(dt, keys);
}

void GameManager::render(float dt) {
    SDL_SetRenderDrawColor(this->renderer, 30, 30, 30, 255);
    SDL_RenderClear(this->renderer);

    this->world->render(this->renderer);

    SDL_RenderPresent(this->renderer);
}

void GameManager::clean() {
    this->world.reset();
    SDL_DestroyTexture(this->warriorRightTexture);
    SDL_DestroyTexture(this->warriorUpTexture);
    SDL_DestroyTexture(this->warriorDownTexture);
    SDL_DestroyTexture(this->warriorIdleDownTexture);
    SDL_DestroyTexture(this->warriorIdleUpTexture);
    SDL_DestroyTexture(this->warriorIdleRightTexture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

GameManager::~GameManager() {
    this->clean();
}
