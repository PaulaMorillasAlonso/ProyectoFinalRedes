#include "GameClient.h"
#include "../NetUtils/Message.h"
#include "SDL2/SDL.h"
void GameClient::login()
{
    std::string msg;
    Message em(nick, msg);
    em.type = Message::LOGIN;

    socket.send(em, socket);
    initClient(720,480);

}
void GameClient::initClient(int w, int h){

	
  /* Initialises data */
  SDL_Window *window = NULL;
  
  /*
  * Initialises the SDL video subsystem (as well as the events subsystem).
  * Returns 0 on success or a negative error code on failure using SDL_GetError().
  */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
  }

  /* Creates a SDL window */
  window = SDL_CreateWindow("SDL Example", /* Title of the SDL window */
			    200, /* Position x of the window */
			    200, /* Position y of the window */
			    w, /* Width of the window in pixels */
			    h, /* Height of the window in pixels */
			    0); /* Additional flag(s) */

  /* Checks if window has been created; if not, exits program */
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
  }
    SDL_Renderer* renderer_ = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


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