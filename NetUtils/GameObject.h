#pragma once
#include <cassert>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../SDL_Utils/Vector2D.h"
#include <string>
#include "SDLGame.h"


class GameObject {

public:
	static int numObjects;
	GameObject();
	GameObject(std::string name);
	virtual ~GameObject();

	virtual void handleInput(const SDL_Event &event) {};
	virtual void update() {};

	inline bool isEnabled() const {
		return enabled_;
	}

	inline bool setEnabled(bool e) {
		return enabled_ = e;
	}

	virtual void render();

	void setTransform(const int x, const int y);

	Vector2D getTransform() const;

	void setTransform(Vector2D tr);

	void setRotation(const float rot);

	void setDimensions(const int w, const int h);

	Vector2D getDimensions() const;

	void setTexture(const std::string& path);
	SDL_Texture* getTexture();
	std::string getName();

protected:
	std::string name_ = "";
	Vector2D tr_;
	Vector2D dim_;

	bool enabled_;
	float rotation;

	SDL_Texture* text_;
	Vector2D textDim_;
    SDL_Rect *texture_rect_;

    SDLGame *game_;
	void render(const SDL_Rect &src, const SDL_Rect &dest,
            const SDL_Point *p = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
};
