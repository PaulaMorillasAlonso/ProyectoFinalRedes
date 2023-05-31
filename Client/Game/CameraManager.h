#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <map>
#include <vector>


#include "../../SDL_Utils/RandomNumberGenerator.h"
#include "../../SDL_Utils/macros.h"
#include "../../NetUtils/GameObject.h"
#include "../../SDL_Utils/Vector2D.h"


class CameraManager {


public:

	CameraManager();
	virtual ~CameraManager();

	// the window's width
	Vector2D getWindowSize();
	Vector2D getRelativeWindowSize();
	
	void setWindowSize(Vector2D limit);
    void scrollY(float center);

	void addScrollingObject(GameObject* obj);

private:
    std::vector<GameObject*> scrollingObjects_;
    float currentHeight_;
};
#endif