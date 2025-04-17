#include <iostream>
#include "Game.h"
#include "Warrior.h"
#include "Slime.h"
#include "Map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "C:\Users\Usuario\OneDrive\Área de Trabalho\Jogo C++\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), player(nullptr) {}

bool colision(float ax, float ay, float aWidth, float aHeight, float bx, float by, float bWidth, float bHeight){
    if( ay+ aHeight < by) return false;
    else if(ay > by + bHeight) return false;
    else if(ax + aWidth < bx) return false;
    else if(ax > bx + bWidth) return false;

    return true; 
}

float getTime(){
    return static_cast<float>(SDL_GetTicks())/1000.0;
}

/*bool Game::loadMap(const char* filePath, SDL_Renderer* renderer) { //função que carrega o mapa
    SDL_Surface* tempSurface = IMG_Load(filePath);
    if(!tempSurface){
        std::cerr << "Erro ao carregar o mapa: " <<   IMG_GetError() << std::endl;
        return false;
    }

    mapTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if(!mapTexture){
        std::cerr << "Erro ao criar a textura do mapa: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}
*/
bool Game::init(const char* title, int width, int height){

    //camera = {0, 0, 800, 600};

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {  
        std::cerr << "Erro ao inicializar o SDL2: " <<   SDL_GetError() << std::endl;
        return -1;
    }

    mapData = new int*[10];
    for(int i = 0; i < 10; i++){
        mapData[i] = new int[10] {
            0, 1, 0, 1, 0, 1, 0, 1, 0, 1
        };
    }

    this->window = SDL_CreateWindow(title,
                            SDL_WINDOWPOS_CENTERED,   
                            SDL_WINDOWPOS_CENTERED,   
                            width, height,    
                            SDL_WINDOW_SHOWN);  

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

    /*if(!loadMap("C:/Users/Usuario/OneDrive/Área de Trabalho/Jogo C++/Eldryn Legends/assets/maps/map.png", renderer)){
        return false;
    }*/


    player = std::make_unique<Warrior>(800 / 2, 600 / 2);
    enemySlime = std::make_unique<Slime>(1000 / 2, 1000 / 2);
    gameMap = std::make_unique<Map>(renderer, "C:/Users/Usuario/OneDrive/Área de Trabalho/Jogo C++/Eldryn Legends/assets/maps/test.png", mapData, 16, 10, 10);

    this->isRunning = true;
    return true;
}

/*void Game::updateCamera(){
    Vector position_p = player->getPosition();
    camera.x = position_p.x - camera.w / 2;
    camera.y = position_p.y - camera.h / 2;

    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    if (camera.x > 1000 - camera.w) camera.x = 1000 - camera.w;
    if (camera.y > 1000 - camera.h) camera.y = 1000 - camera.h;
}*/


void Game::run(){   
    float previousTime = getTime();
        while(isRunning){
            float currentTime = getTime();
            float dt = currentTime - previousTime;
            previousTime = currentTime;

            Vector position_slime = enemySlime->getPosition();
            Vector position_player = player->getPosition();
            if(colision(position_slime.x, position_slime.y, 32, 32, position_player.x, position_player.y, 64, 64)){
                std::cout<< "tocou" << std::endl;

            }
        
            render(dt);
            handleEvents(dt);
            SDL_Delay(30);
        }
}

void Game::handleEvents(float dt){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            isRunning = false;
        }
    }

    //updateCamera();

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    player->handleEvents(dt, keys);
    enemySlime->movimentation(dt);
}

void Game::render(float dt){
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    /*SDL_Rect srcRect = {camera.x, camera.y, camera.w, camera.h};
    SDL_Rect destRect = { 0, 0, camera.w, camera.h };*/

    gameMap->render(renderer);
    player->render(renderer);
    enemySlime->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::clean(){
    for(int p = 0; p < 10; p++){
        delete[] mapData[p];
    }
    delete[] mapData;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Game::~Game(){
    clean();
}