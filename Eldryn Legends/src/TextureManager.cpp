#include "TextureManager.h"
#include <SDL2/SDL_image.h>
#include <iostream>

bool TextureManager::load(const std::string& id, SDL_Renderer* renderer, const std::string& filePath){
    SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
    if (!tempSurface) {
        std::cerr << "Failed to load image: " << filePath << " - " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);     
    if (!texture) {
        std::cerr << "Failed to create texture from: " << filePath << " - " << SDL_GetError() << std::endl;
        return false;
    }
    
    textures[id] = texture;
    return true;
}

SDL_Texture* TextureManager::get(const std::string& id) const{
    auto it = textures.find(id);
    return(it != textures.end()) ? it->second : nullptr;
}

void TextureManager::clean(){
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}