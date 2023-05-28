#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <map>
#include <vector>

#include "../../SDL_Utils/Singleton.h"
#include "../../SDL_Utils/RandomNumberGenerator.h"
#include "../../SDL_Utils/macros.h"
#include "../../SDL_Utils/GameObject.h"
#include "../../SDL_Utils/Vector2D.h"


class CameraManager: public Singleton<CameraManager> {

	friend Singleton<CameraManager> ; // needed to give access to private constructors

public:

	virtual ~CameraManager();

	// cannot copy/move
	CameraManager(CameraManager&) = delete;
	CameraManager(CameraManager&&) = delete;
	CameraManager& operator=(CameraManager&) = delete;
	CameraManager& operator=(CameraManager&&) = delete;

	// the window's width
	Vector2D getWindowSize();
	Vector2D getRelativeWindowSize();
	
	void setWindowSize(Vector2D limit);
    void scrollY(float center);

private:
	CameraManager();
    std::vector<GameObject*> scrollingObjects_;
    float currentHeight_;
};
#endif

// This macro defines a compact way for using the singleton CameraManager, instead of
// writing CameraManager::instance()->method() we write CameraManager().method()
//
inline CameraManager& GameManager() {
	return *CameraManager::instance();
}