/*
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <map>
#include <list>


#include "../../SDL_Utils/RandomNumberGenerator.h"
#include "../../SDL_Utils/macros.h"
#include "../../SDL_Utils/GameObject.h"
#include "../../SDL_Utils/Vector2D.h"


class PlatformManager {


public:

	PlatformManager();
	virtual ~PlatformManager();

    Platform* createPlatform();
    void removePlatform(Platform* platform);
    std::list<Platform*> getPlatforms();


private:

    std::list<Platform*> platforms_;

    int minPlatformDistance_;
    int maxPlatformDistance_;

    int leftMostPos_;
    int rightMostPos_;
};
#endif
*/