#pragma once
#include <SDL2/SDL.h>

class Map{
private:
    SDL_Texture* tileset;
    int tileSize;
    int mapW;
    int mapH;
    int** mapData;
    SDL_Rect srcRect, destRect;
public:
    Map(SDL_Renderer* renderer, const char* tilesetPath, int** data, int tileSize, int mapW, int mapH);
    ~Map();
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);
};