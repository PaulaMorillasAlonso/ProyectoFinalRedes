#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class SDLGame
{
private:
	///<summary>Variables basicas de SDL</summary>
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Surface* surface_ = nullptr;

	///<summary>Manager que gestiona las texturas </summary>
	//TextureManager* textureManager_ = nullptr;

    void initSDL();
	///<summary>Metodo que inicializa los recursos de la app</summary>
	//void initResources();


	SDLGame();

	static SDLGame* instance;
	SDL_Texture* ourBG_;
public:
  
  	static SDLGame* GetInstance();

	SDLGame(SDLGame &other) = delete;
    void operator=(const SDLGame &) = delete;
    
    ~SDLGame();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	void loadImage(std::string name);
	SDL_Surface* getSurface();

	SDL_Texture * getTexture();
	void destroyWindow();

    ///<summary>Constantes con las dimensiones de la ventana </summary>
	static const int winWidth_ = 720;
	static const int winHeight_ = 480; 
};