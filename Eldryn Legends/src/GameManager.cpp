#include "GameManager.h"
#include "GameWorld.h"
#include "GlobalProperties.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "C:\Users\Usuario\OneDrive\Área de Trabalho\Jogo C++\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

float getTime(){
    return static_cast<float>(SDL_GetTicks())/1000.0;
}

GameManager::GameManager() : window(nullptr), renderer(nullptr), isRunning(false) {}

bool GameManager::init(const char* title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {  
        std::cerr << "Erro ao inicializar o SDL2: " <<   SDL_GetError() << std::endl;
        return -1;
    }

    this->window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,   
        SDL_WINDOWPOS_CENTERED,   
        width, height,    
        SDL_WINDOW_SHOWN);  

    //Tela cheia
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!this->window) {
        std::cerr << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->renderer) { 
        std::cerr << "Erro ao criar o renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return false;
    }   

    
    SDL_RenderSetLogicalSize(renderer, BASE_WIDTH, BASE_HEIGHT);

    world = std::make_unique<GameWorld>(renderer);
    this->isRunning = true;
    return true;
}

void GameManager::run(){
    float previousTime = getTime();
        while(isRunning){
            float currentTime = getTime();
            float dt = currentTime - previousTime;
            previousTime = currentTime;
        
            world->update(dt);
            render(dt);
            handleEvents(dt);
            SDL_Delay(30);
        }
}

void GameManager::handleEvents(float dt){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            isRunning = false;
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    world->handleInput(dt, keys);
}

void GameManager::render(float dt){
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    world->render(renderer);

    SDL_RenderPresent(renderer);
}

void GameManager::clean(){
    world.reset();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

GameManager::~GameManager(){
    clean();
}