#pragma once
#include <SDL2/SDL.h>

class SDLGame
{
private:
	///<summary>Variables basicas de SDL</summary>
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;

	///<summary>Manager que gestiona las texturas </summary>
	//TextureManager* textureManager_ = nullptr;

    void initSDL();
	///<summary>Metodo que inicializa los recursos de la app</summary>
	void initResources();


	SDLGame();

	static SDLGame* instance;

public:
  
  	static SDLGame* GetInstance();

	SDLGame(SDLGame &other) = delete;
    void operator=(const SDLGame &) = delete;
    
    ~SDLGame();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

	void destroyWindow();

    ///<summary>Constantes con las dimensiones de la ventana </summary>
	static const int winWidth_ = 720;
	static const int winHeight_ = 480; 
};