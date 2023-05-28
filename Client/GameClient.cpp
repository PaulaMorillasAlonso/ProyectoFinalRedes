#include "GameClient.h"

#include "../NetUtils/Message.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
void GameClient::login()
{
    std::string msg;
    Message em(nick, msg);
    em.type = Message::LOGIN;

    socket.send(em, socket);
    initClient(720,480);

}
void GameClient::initClient(int w, int h){

    
	/* SDL_Window* window=nullptr;

    //Inicializa el subsistema de sdl
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("Moodle Jump",20, 20, 640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // Sinicializa la libreria de sdl image
    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if((initStatus & flags) != flags){
        std::cout << "SDL2_Image format not available" << std::endl;
    }

    SDL_Surface* image;
    image = IMG_Load("images/mario.png");
    if(!image){
        std::cout << "Image not loaded..." << std::endl;
    }

    SDL_Texture* ourPNG = SDL_CreateTextureFromSurface(renderer, image);

    // loop mientras no se cierre la ventana
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }

        }
        // (2) Handle Updates
        
        // limpia la pantalla
        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,ourPNG,NULL,NULL);

        // Renderizalo que hemos dibujado
        SDL_RenderPresent(renderer);
    }

    // Destruimos la ventana
    SDL_DestroyWindow(window);
    
    // liberamos superficie de la imagen
    SDL_FreeSurface(image);
    // destruimos la textura
    SDL_DestroyTexture(ourPNG);

    IMG_Quit();

    // Salimos.
    SDL_Quit();*/

  

}
void GameClient::logout()
{
    std::string msg;

    Message em(nick, msg);
    em.type = Message::LOGOUT;

    socket.send(em, socket);

}

void GameClient::input_thread()
{
    while (true)
    {
        char buffer[Message::MESSAGE_SIZE];
        std::cin.getline(buffer, Message::MESSAGE_SIZE);
        if (strcmp(buffer, "q") == 0) {
            logout();
            break;
        }
        else {
            Message msg(nick, buffer);
            msg.type = Message::MESSAGE;
            socket.send(msg, socket);
        }
    }
}

void GameClient::net_thread()
{
    while (true)
    {
        Message msg;
        socket.recv(msg);
        std::cout << msg.nick << ": " << msg.message << "\n";

    }
}