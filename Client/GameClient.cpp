#include "GameClient.h"

#include "../NetUtils/Message.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../NetUtils/SDLGame.h"
#include "Game/Player.h"
#include "../NetUtils/GameObject.h"
void GameClient::login()
{
    std::string msg;
    Message em(nick, msg);
    em.type = Message::LOGIN;

    socket.send(em, socket);
    initClient();

}
void GameClient::initClient(){

    //Crea una ventana
    game_= SDLGame::GetInstance();
    //Crea un jugador
    gameObject_= new GameObject();
    gameObject_->setTransform(0,0);
    gameObject_->setTexture("Assets/platform.png");
    gameObject_->setDimensions(100,100);

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
    while(gameIsRunning_){
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning_= false;
            }

        }
        
        //Message msg(nick, buffer);
        //msg.type = Message::MESSAGE;
        //socket.send(msg, socket);
        
    }
    logout();
}
void GameClient::render() const{

   if(gameIsRunning_){

        //gameObject_->render();
        // (2) Handle Updates
        SDL_SetRenderDrawColor(game_->getRenderer(),0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(game_->getRenderer());

        SDL_RenderCopy(game_->getRenderer(),game_->getTexture(),NULL,NULL);
        SDL_Rect location = {gameObject_->getTransform().getX(),gameObject_->getTransform().getY(),
                            gameObject_->getDimensions().getX(),gameObject_->getDimensions().getY()}; 
     

        SDL_RenderCopy(game_->getRenderer(),gameObject_->getTexture(),NULL,&location);

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