/*
#include "PlatformManager.h"

#include <cassert>
#include <cstdlib>

PlatformManager::PlatformManager() {
    
}

PlatformManager::~PlatformManager() {
}

Platform* PlatformManager::createPlatform() {
    Platform* p = new Platform();
    platforms_.push_back(p);

    int x;
    // Get random between leftMost and RightMost
    // This makes x
    x = rand() % rightMostPos_ + leftMostPos_;

    int y;
    // Get random between minPlatformDistance & max
    // Add random to platforms_.front()'s height
    // This makes y
    y = rand() % maxPlatformDistance_ + minPlatformDistance_ + platforms_.front().getTransform().getY();

    p->setTransform(Vector2D(x, y));

    return p;
}

// Call this from Manager to remove from list only, not delete.
void PlatformManager::removePlatform(Platform* platform) {
    platforms_.erase(platform);
}

std::list<Platform*> PlatformManager::getPlatforms() {
    return platforms_;
}
*/