#include "CameraManager.h"

#include <cassert>

CameraManager::CameraManager() {
    // Igual hace falta WindowHeight
}

CameraManager::~CameraManager() {
}

void CameraManager::scrollY(float center) {
    float moveY = center - currentHeight_;

    /*for (int i = 0; i < scrollingObjects_.size(); i++) {
        scrollingObjects_[i].getTransform().setY(scrollingObjects_[i].getTransform().getY() + moveY);
        // if (scrollingObjects_[i].getTransform().getY() >? <?)
        // Si se sale de pantalla, desactivar.
    }*/
}