#include "GameClient.h"

#include "../NetUtils/Message.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../NetUtils/SDLGame.h"
void GameClient::login()
{
    std::string msg;
    Message em(nick, msg);
    em.type = Message::LOGIN;

    socket.send(em, socket);
    initClient(720,480);

}
void GameClient::initClient(int w, int h){

    game_= SDLGame::GetInstance();
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
void GameClient::render() const{
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
        SDL_SetRenderDrawColor(game_->getRenderer(),0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(game_->getRenderer());

        SDL_RenderCopy(game_->getRenderer(),game_->getTexture(),NULL,NULL);

        // Renderizalo que hemos dibujado
        SDL_RenderPresent(game_->getRenderer());
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