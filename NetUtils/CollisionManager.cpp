#include "CollisionManager.h"

#include <cassert>

CollisionManager::CollisionManager() : finished_(false) {
}

CollisionManager::~CollisionManager() {
}

bool CollisionManager::checkPlayerPlatformsCollisions(float playerVelY, Vector2D playerPos, Vector2D playerDim,Vector2D platDim) {
    for(Vector2D& p : platformPositions_) {

        if (playerVelY > 0 && overlap(playerPos, playerDim, p, platDim)){
            if (p.getY() == platformPositions_[platformPositions_.size() - 1].getY())
                finished_ = true;
            return true;
        }
    }
    return false;
}

void CollisionManager::addPlatforms(Vector2D pos){
    platformPositions_.push_back(pos);
}

void CollisionManager::scrollPlatforms(int scrollY)
{
    
    for (Vector2D& p : platformPositions_){
        p.setY(p.getY() + scrollY);
    }
    
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