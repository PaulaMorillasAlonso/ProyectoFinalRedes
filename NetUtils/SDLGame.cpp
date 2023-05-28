#include "SDLGame.h"
#include "iostream"
#include <SDL2/SDL.h>

SDLGame* SDLGame::instance = nullptr;

SDLGame::SDLGame(){
    initSDL();
	initResources();
}

SDLGame::~SDLGame(){
	destroyWindow();
}

void SDLGame::initSDL(){
    int winX, winY; // PosiciOn de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;
	// InicializaciOn del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Moodle Jump!", winX, winY, winWidth_,
		winHeight_, SDL_WINDOW_SHOWN);
	  

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == NULL || renderer_ == NULL) {
		std::cout<< "Game window or renderer was null \n";
	}

}

SDLGame* SDLGame::GetInstance()
{
	if(instance==nullptr){
    	instance = new SDLGame();
    }
    return instance;
}

SDL_Window* SDLGame::getWindow(){
	return window_;
}

SDL_Renderer* SDLGame::getRenderer(){
	return renderer_;
}

/*TextureManager* SDLGame::getTextureManager(){
	return textureManager_;
}*/

void SDLGame::initResources(){

	//Crear e inicializar textureManager
	/*textureManager_ = new TextureManager();
	textureManager_->initObject();

	//Creacion de las texturas
	for (auto& image : Resources::imageRoutes) {
		textureManager_->loadFromImg(image.textureId, renderer_, image.filename);
	}*/
}

void SDLGame::destroyWindow(){
	//Destruimos textureManager
	//delete textureManager_;

    //Destruimos render y window
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	renderer_ = nullptr;
	window_ = nullptr;

	//Cerramos SDL
	SDL_Quit();
}