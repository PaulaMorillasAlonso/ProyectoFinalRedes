#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "Platform.h"
#include "Player.h"
#include "../../SDL_Utils/Vector2D.h"


class CollisionManager {


public:

	CollisionManager();
	virtual ~CollisionManager();

    bool checkPlayerPlatformsCollisions();

    void addPlatform(Platform* p);

    void setPlayer(Player* p);

    bool touchedLast(){
        return finished_;
    }

private:

    bool overlap(Vector2D tr1, Vector2D dim1, Vector2D tr2, Vector2D dim2);

    std::vector<Platform*> collisionPlatforms_;
    Player* player_;
    bool finished_;

    int windowHeight_;
};