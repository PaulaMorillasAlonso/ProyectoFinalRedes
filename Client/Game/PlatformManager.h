#ifndef PLATFORMMANAGER_H
#define PLATFORMMANAGER_H

#include <string>
#include <map>
#include <list>


#include "../../SDL_Utils/RandomNumberGenerator.h"
#include "../../SDL_Utils/macros.h"
#include "../../NetUtils/GameObject.h"
#include "../../SDL_Utils/Vector2D.h"
#include "Platform.h"


class PlatformManager {


public:

	PlatformManager();
	virtual ~PlatformManager();

    Platform* createPlatform();
    Platform* createPlatform(Vector2D where);
    Platform* createPlatform(Vector2D where, Vector2D size);
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