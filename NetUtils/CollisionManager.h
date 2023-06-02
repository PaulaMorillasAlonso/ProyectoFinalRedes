#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "../SDL_Utils/Vector2D.h"


class CollisionManager {


public:

	CollisionManager();
	virtual ~CollisionManager();

    bool checkPlayerPlatformsCollisions(float playerVelY, Vector2D playerPos, Vector2D playerDim,Vector2D platDim);

    void addPlatforms(Vector2D platPos);
    void scrollPlatforms(int scrollY);

    bool touchedLast(){
        return finished_;
    }

private:

    bool overlap(Vector2D pPos, Vector2D pDim, Vector2D platPos, Vector2D platDim);

    std::vector<Vector2D> platformPositions_;
    bool finished_;

};