#include "GameClient.h"

#include "../NetUtils/Message.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../NetUtils/SDLGame.h"
#include "Game/Player.h"
#include "../NetUtils/ObjectManager.h"

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
    objMan_= new ObjectManager();

    /*gameObject_= new GameObject();
    gameObject_->setTransform(0,0);
    gameObject_->setTexture("Assets/platform.png");
    gameObject_->setDimensions(100,100);
    
    objMan_->addObject(gameObject_);


    GameObject *gameObject= new GameObject();
    gameObject->setTransform(100,100);
    gameObject->setTexture("Assets/platform.png");
    gameObject->setDimensions(100,100);
    objMan_->addObject(gameObject);*/

    //Crea un jugador
    myPlayer1_= new Player(this);
    myPlayer1_->setTexture("Assets/player1.png");
    myPlayer1_->setTransform(200,300);
    myPlayer1_->setDimensions(100,100);
    objMan_->addObject(myPlayer1_);

    myPlayer2_= new Player(this);
    myPlayer2_->setTexture("Assets/player2.png");
    myPlayer2_->setTransform(500,300);
    myPlayer2_->setDimensions(100,100);
    objMan_->addObject(myPlayer2_);

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

        //Pintado de fondo
        SDL_SetRenderDrawColor(game_->getRenderer(),0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(game_->getRenderer());

        SDL_RenderCopy(game_->getRenderer(),game_->getTexture(),NULL,NULL);

        //Pintado de los GameObjects
        for (const auto& pair : objMan_->getObjects()) {
      
        GameObject * obj = pair.second;
        SDL_Rect location = {obj->getTransform().getX(),obj->getTransform().getY(),
                            obj->getDimensions().getX(),obj->getDimensions().getY()}; 
     
        SDL_RenderCopy(game_->getRenderer(),obj->getTexture(),NULL,&location);
       
    }
        

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