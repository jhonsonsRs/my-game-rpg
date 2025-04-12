#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "C:\Users\Usuario\OneDrive\Área de Trabalho\Jogo C++\Eldryn Legends\math-vector.h"
using Vector = Mylib::Math::Vector<float, 2>;

class World{
private:
    SDL_Texture* mapTexture;
    SDL_Rect mapRect;
    SDL_Rect camera;
    std::vector<Entity*> entities; //tem um uso menor de memória do que uma lista, tem uma perfomance ótima em jogos
public:
    World(int w, int h){}
    ~Map();

    void loadMap(SDL_Renderer* renderer, const char* path);
    void update(float dt);
    void render(SDL_Renderer* renderer, SDL_Rect camera);
    void addEntity(Entity* entity);

    SDL_Rect getMapRect() const {
        return mapRect;
    }
};