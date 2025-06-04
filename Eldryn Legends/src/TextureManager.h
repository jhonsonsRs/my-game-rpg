#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>

class TextureManager{
private:
    std::unordered_map<std::string, SDL_Texture*> textures;
public:
    bool load(const std::string& id, SDL_Renderer* renderer, const std::string& filePath );
    SDL_Texture* get(const std::string& id) const;
    void clean();
};