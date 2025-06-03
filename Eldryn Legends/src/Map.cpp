#include "Map.h"
#include <SDL2/SDL_image.h>
#include "GlobalProperties.h"

Map::Map(SDL_Renderer* renderer, const char* tilesetPath, int** data, int tileSize, int mapW, int mapH)
    : tileSize(tileSize), mapData(data), mapW(mapW), mapH(mapH) {
    SDL_Surface* tempSurface = IMG_Load(tilesetPath);
    this->tileset = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

Map::~Map() {
    SDL_DestroyTexture(this->tileset);
}

void Map::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    int tilesPerRow = 7;
    for (int y = 0; y < this->mapH; ++y) {
        for (int x = 0; x < this->mapW; ++x) {
            int tileID = this->mapData[y][x];

            this->srcRect.x = (tileID % tilesPerRow) * this->tileSize;
            this->srcRect.y = (tileID / tilesPerRow) * this->tileSize;
            this->srcRect.w = this->srcRect.h = this->tileSize;

            this->destRect.x = x * this->tileSize - camera.x;
            this->destRect.y = y * this->tileSize - camera.y;
            this->destRect.w = this->destRect.h = this->tileSize;

            SDL_RenderCopy(renderer, this->tileset, &this->srcRect, &this->destRect);
        }
    }
}