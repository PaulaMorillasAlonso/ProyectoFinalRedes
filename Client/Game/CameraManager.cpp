#include "CameraManager.h"

#include <cassert>
#include <iostream>

CameraManager::CameraManager() {
    // Igual hace falta WindowHeight
}

CameraManager::~CameraManager() {
}

void CameraManager::setWindowHeight(int h) {
    totalHeight_ = h;
    currentHeight_ = h / 2;
}

void CameraManager::addScrollingObject(GameObject* obj) {
    scrollingObjects_.push_back(obj);
}

void CameraManager::addPlayer(Player* p) {
    players_.push_back(p);
    addScrollingObject(p);
}


void CameraManager::checkPlayersHeightAndScroll() {
    for (Player* p : players_){
        if (p->getTransform().getY() < currentHeight_){
            scrollY(p->getTransform().getY());
        }
    }
}

void CameraManager::scrollY(float center) {
    float moveY = currentHeight_ - center;
    // std::cout << "Scrolling " << moveY << "\n";

    for (GameObject* g : scrollingObjects_) {
        g->setTransform(g->getTransform().getX(), g->getTransform().getY() + moveY);
        // g->getTransform().setY(g->getTransform().getY() + moveY);
    }
}