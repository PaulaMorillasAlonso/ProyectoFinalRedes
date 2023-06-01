#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>


#include "../../SDL_Utils/RandomNumberGenerator.h"
#include "../../SDL_Utils/macros.h"
#include "../../NetUtils/GameObject.h"
#include "Platform.h"
#include "Player.h"
#include "../../SDL_Utils/Vector2D.h"


class CollisionManager {


public:

	CollisionManager();
	virtual ~CollisionManager();

    bool checkPlayerPlatformsCollisions() {
        for(Platform* p : collisionPlatforms_) {

            std::cout << "Overlap!\n";

            if (player_->getVelY() > 0 && overlap(player_->getTransform(), player_->getDimensions(), p->getTransform(), p->getDimensions())){
                return true;
            }
        }
        return false;
    }

    void addPlatform(Platform* p){
        collisionPlatforms_.push_back(p);
            std::cout << "Platform Count: " << collisionPlatforms_.size() << "\n";
    }

    void setPlayer(Player* p){
        player_ = p;
    }

private:

    bool overlap(Vector2D tr1, Vector2D dim1, Vector2D tr2, Vector2D dim2){

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

    std::vector<Platform*> collisionPlatforms_;
    Player* player_;

    int windowHeight_;
};
#endif