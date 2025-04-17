#include "Map.h"
#include <SDL2/SDL_image.h>

Map::Map(SDL_Renderer* renderer, const char* tilesetPath, int** data, int tileSize, int mapW, int mapH) :
    tileSize(tileSize), mapData(data), mapW(mapW), mapH(mapH){
        SDL_Surface* tempSurface = IMG_Load(tilesetPath);
        tileset = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
    }

Map::~Map(){
    SDL_DestroyTexture(tileset);
}

void Map::render(SDL_Renderer* renderer){
    for (int y = 0; y < mapH; ++y) {
        for (int x = 0; x < mapW; ++x) {
            int tileID = mapData[y][x];

            srcRect.x = (tileID % 8) * tileSize;
            srcRect.y = (tileID / 8) * tileSize;
            srcRect.w = srcRect.h = tileSize;

            destRect.x = x * tileSize;
            destRect.y = y * tileSize;
            destRect.w = destRect.h = tileSize;

            SDL_RenderCopy(renderer, tileset, &srcRect, &destRect);
        }
    }
}