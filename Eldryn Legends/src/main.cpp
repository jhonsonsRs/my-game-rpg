#include "Game.h"

int main(int argc, char* argv[]){
    Game game;

    if(!game.init("MonkeyQuest", 800, 600)){
        return -1;
    }

    game.run();
    return 0;
}