#include "GameManager.h"
#include "GameWorld.h"
#include "GlobalProperties.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "C:\Games\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

float getTime() {
    return static_cast<float>(SDL_GetTicks()) / 1000.0;
}

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() : window(nullptr), renderer(nullptr), isRunning(false) {
    instance = this;
}

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

    initAudio();

    musicFiles = {
        "C:/Games/Eldryn Legends/assets/sounds/track1.mp3",
        "C:/Games/Eldryn Legends/assets/sounds/track2.mp3",
        "C:/Games/Eldryn Legends/assets/sounds/track3.mp3",
        "C:/Games/Eldryn Legends/assets/sounds/track4.mp3"
    };

    playRandomMusic();

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

    //potion
    textureManager.load("health_potion", renderer, "C:/Games/Eldryn Legends/assets/sprites/potion.png");


    SDL_RenderSetLogicalSize(this->renderer, BASE_WIDTH, BASE_HEIGHT);

    this->world = std::make_unique<GameWorld>(this->renderer, &textureManager);
    this->isRunning = true;
    return true;
}

void GameManager::initAudio(){
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer não pôde ser inicializado! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }
    
    // Volume inicial (0-128)
    Mix_VolumeMusic(30);
}

void GameManager::playRandomMusic() {
    if (musicPlaying) {
        Mix_HaltMusic();
    }
    
    // Inicializa o gerador de números aleatórios (só precisa ser feito uma vez)
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
    
    // Sorteia uma música aleatória usando rand()
    int randomIndex = std::rand() % musicFiles.size();
    currentMusic = Mix_LoadMUS(musicFiles[randomIndex].c_str());
    
    if (!currentMusic) {
        std::cerr << "Falha ao carregar música! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }
    
    if (Mix_PlayMusic(currentMusic, 0)) {
        std::cerr << "Falha ao tocar música! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }
    
    musicPlaying = true;
    
    // Configura um callback para quando a música terminar
    Mix_HookMusicFinished([]() {
        GameManager::getInstance().musicFinished();
    });
}

void GameManager::musicFinished(){
    musicPlaying = false;
    playRandomMusic(); // Toca a próxima música
}

void GameManager::cleanAudio() {
    if (currentMusic) {
        Mix_FreeMusic(currentMusic);
        currentMusic = nullptr;
    }
    Mix_CloseAudio();
}


void GameManager::run() {
    float previousTime = getTime();
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    while (this->isRunning) {
        float currentTime = getTime();
        float dt = currentTime - previousTime;
        previousTime = currentTime;

        this->world->update(dt, keys, this->renderer);
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
    this->clean();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    cleanAudio();
}

GameManager::~GameManager() {
    this->clean();
}