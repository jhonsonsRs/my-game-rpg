#include "Camera.h"
#include "GlobalProperties.h"

Camera::Camera(){viewBox = {0, 0, BASE_WIDTH, BASE_HEIGHT};}

void Camera::update(int targetX, int targetY, int mapW, int mapH){
    viewBox.x = targetX - BASE_WIDTH / 2;
    viewBox.y = targetY - BASE_HEIGHT / 2;

    if(viewBox.x < 0){
        viewBox.x = 0;
    }

    if(viewBox.y < 0){
        viewBox.y = 0;
    }

    if(viewBox.x + BASE_WIDTH > mapW) {
        viewBox.x = mapW - BASE_WIDTH;
    }

    if(viewBox.y + BASE_HEIGHT > mapH){
        viewBox.y = mapH - BASE_HEIGHT;
    }
}

SDL_Rect Camera::getView() const {
    return viewBox;
}