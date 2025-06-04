#include "Camera.h"
#include "GlobalProperties.h"
#include <algorithm>

Camera::Camera() {
    this->viewBox = { 0, 0, BASE_WIDTH, BASE_HEIGHT };
}

void Camera::update(int targetX, int targetY, int mapW, int mapH) {
    const int halfWidth = BASE_WIDTH / 2;
    const int halfHeight = BASE_HEIGHT / 2;

    this->viewBox.x = std::clamp(targetX - halfWidth, 0, mapW - BASE_WIDTH);
    this->viewBox.y = std::clamp(targetY - halfHeight, 0, mapH - BASE_HEIGHT);
}

SDL_Rect Camera::getView() const {
    return this->viewBox;
}
