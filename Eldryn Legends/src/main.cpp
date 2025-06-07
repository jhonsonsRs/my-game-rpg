#include "GameManager.h"
#include "GlobalProperties.h"

int main(int argc, char* argv[]){
    GameManager game;

    srand(time(0));
    if(!game.init("Eldryn Legends", SCREEN_WIDTH, SCREEN_HEIGHT)){
        return -1;
    }

    game.run();
    return 0;
}