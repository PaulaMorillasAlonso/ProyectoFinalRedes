#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "../../SDL_Utils/RandomNumberGenerator.h"
#include "../../SDL_Utils/macros.h"
#include "../../SDL_Utils/Vector2D.h"


class GameManager {
	
public:

	GameManager();
	virtual ~GameManager();

	// the window's width
	Vector2D getWindowSize();
	Vector2D getRelativeWindowSize();
	
	void setWindowSize(Vector2D limit);

private:
	Vector2D windowSize_;
	Vector2D relativeSize_;
};
#endif