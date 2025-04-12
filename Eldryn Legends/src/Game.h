#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "C:\Users\Usuario\OneDrive\Área de Trabalho\Jogo C++\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

class Warrior;
class Slime;

class Game{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* mapTexture;
    SDL_Rect mapRect;
    SDL_Rect camera;
    bool isRunning;


    std::unique_ptr<Warrior> player;
    std::unique_ptr<Slime> enemySlime;
    //ponteiro inteligente que gerencia memória de forma automática. 
    //não precisa usar delete
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    bool loadMap(const char* filePath, SDL_Renderer* renderer);
    void updateCamera();
    void handleEvents(float dt);
    void clean();
    void render(float dt);
    void run();

    SDL_Renderer* getRenderer() const {
        return this->renderer;
    }

};