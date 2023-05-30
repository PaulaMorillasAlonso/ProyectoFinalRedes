#include "SDLGame.h"
#include "iostream"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
SDLGame* SDLGame::instance = nullptr;

SDLGame::SDLGame(){
    initSDL();
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
		winHeight_,SDL_WINDOW_RESIZABLE);
	  

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
	if (window_ == NULL || renderer_ == NULL) {
		std::cout<< "Game window or renderer was null \n";
	}
    // Sinicializa la libreria de sdl image
    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if((initStatus & flags) != flags){
        std::cout << "SDL2_Image format not available" << std::endl;
    }
    loadImage("mario.png");

}
void SDLGame::loadImage(std::string name){

    std::string s = "Assets/"+name;
    const int length = s.length();
    
    char* char_array = new char[length + 1];
  
    strcpy(char_array, s.c_str());

    surface_ = IMG_Load(char_array);
    if(!surface_){
        std::cout << "Image not loaded..." << std::endl;
    }

    ourBG_ = SDL_CreateTextureFromSurface(renderer_, surface_);
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
SDL_Surface*SDLGame::getSurface(){
    return surface_;
}
SDL_Texture *SDLGame::getTexture(){
    return ourBG_;
}

void SDLGame::destroyWindow(){

    // liberamos superficie de la imagen
    SDL_FreeSurface(surface_);
    // destruimos la textura
    SDL_DestroyTexture(ourBG_);

    IMG_Quit();

    //Destruimos render y window
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	renderer_ = nullptr;
	window_ = nullptr;
    surface_=nullptr;
    ourBG_=nullptr;

	//Cerramos SDL
	SDL_Quit();
}