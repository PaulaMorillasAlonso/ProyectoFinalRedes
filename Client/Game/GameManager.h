/*#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "../../SDL_Utils/RandomNumberGenerator.h"
#include "../../SDL_Utils/macros.h"
#include "../../SDL_Utils/Vector2D.h"

class GameManager{

	
public:

	virtual ~GameManager();

	// cannot copy/move
	GameManager(GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager&) = delete;
	GameManager& operator=(GameManager&&) = delete;

	// the window's width
	Vector2D getWindowSize();
	Vector2D getRelativeWindowSize();
	
	void setWindowSize(Vector2D limit);

private:
	GameManager();
	Vector2D windowSize_;
	Vector2D relativeSize_;
};
#endif*/

// This macro defines a compact way for using the singleton GameManager, instead of
// writing GameManager::instance()->method() we write GameManager().method()
//
/*inline GameManager& GameManager() {
	return *GameManager::instance();
}*/