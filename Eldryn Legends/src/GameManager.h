#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <SDL2/SDL_ttf.h>
#include "TextureManager.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <string>

class GameWorld;
class TextureManager;

class GameManager{
private:
    static GameManager* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    TextureManager textureManager;

    std::vector<std::string> musicFiles;
    Mix_Music* currentMusic;
    bool musicPlaying;

    std::unique_ptr<GameWorld> world;
    SDL_Texture* loadTexture(const char* path);
public:
    GameManager();
    ~GameManager();

    //sounds
    void initAudio();
    void playRandomMusic();
    void cleanAudio();
    void musicFinished();

    bool init(const char* title, int width, int height);
    void handleEvents(float dt);
    void render(float dt);
    void clean();
    void run();

    //Singleton: garante que uma classe tenha uma instancia e fornece um ponto de acesso global
    static GameManager& getInstance() {
        return *instance;
    }
};