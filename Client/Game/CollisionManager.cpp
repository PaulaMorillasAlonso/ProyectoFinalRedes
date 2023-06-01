#include "CollisionManager.h"

#include <cassert>

CollisionManager::CollisionManager() : finished_(false) {
    // Igual hace falta WindowHeight
}

CollisionManager::~CollisionManager() {
}

bool CollisionManager::checkPlayerPlatformsCollisions() {
    for(Platform* p : collisionPlatforms_) {

        if (player_->getVelY() > 0 && overlap(player_->getTransform(), player_->getDimensions(), p->getTransform(), p->getDimensions())){
            if (p == collisionPlatforms_[collisionPlatforms_.size() - 1])
                finished_ = true;
            return true;
        }
    }
    return false;
}

void CollisionManager::addPlatform(Platform* p){
    collisionPlatforms_.push_back(p);
    std::cout << "Platform Count: " << collisionPlatforms_.size() << "\n";
}

void CollisionManager::setPlayer(Player* p){
    player_ = p;
    std::cout << "Player Set\n";
}

bool CollisionManager::overlap(Vector2D tr1, Vector2D dim1, Vector2D tr2, Vector2D dim2){

    bool overlapX = false;
    bool overlapY = false;

    if ((tr1.getX() < tr2.getX() && tr1.getX() + dim1.getX() > tr2.getX()) ||
    (tr2.getX() < tr1.getX() && tr2.getX() + dim2.getX() > tr1.getX()))
        overlapX = true;

    if ((tr1.getY() < tr2.getY() && tr1.getY() + dim1.getY() > tr2.getY()) ||
    (tr2.getY() < tr1.getY() && tr2.getY() + dim2.getY() > tr1.getY()))
        overlapY = true;

    return overlapX && overlapY;
}