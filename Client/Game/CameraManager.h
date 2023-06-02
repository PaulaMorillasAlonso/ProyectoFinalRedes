#pragma once
#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <string>
#include <map>
#include <vector>


#include "../../SDL_Utils/RandomNumberGenerator.h"
#include "../../SDL_Utils/macros.h"
#include "../../NetUtils/GameObject.h"
#include "../../SDL_Utils/Vector2D.h"
#include "Player.h"


class CameraManager {


public:

	CameraManager();
	virtual ~CameraManager();
	
	void setWindowHeight(int h);
    void scrollY(int scrollY);

	void addScrollingObject(GameObject* obj);
	void addPlayer(Player* p);

private:
    std::vector<GameObject*> scrollingObjects_;
	std::vector<Player*> players_;
    int currentHeight_;
	int totalHeight_;
};
#endif