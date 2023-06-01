#include "PlatformManager.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

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
    y = rand() % maxPlatformDistance_ + minPlatformDistance_ + platforms_.front()->getTransform().getY();

    p->setTransform(Vector2D(x, y));

    return p;
}

Platform *PlatformManager::createPlatform(Vector2D where)
{
    return createPlatform(where, Vector2D(150, 30));
}

Platform *PlatformManager::createPlatform(Vector2D where, Vector2D size)
{
    Platform* p = new Platform();
    p->setDimensions(size.getX(), size.getY());
    p->setTransform(where);
    p->setTexture("Assets/platform.png");

    std::cout << "Pos: (" << p->getTransform().getX() << ", " << p->getTransform().getY() << ")\n";

    return p;
}

// Call this from Manager to remove from list only, not delete.
void PlatformManager::removePlatform(Platform* platform) {
    platforms_.remove(platform);
}

std::list<Platform*> PlatformManager::getPlatforms() {
    return platforms_;
}