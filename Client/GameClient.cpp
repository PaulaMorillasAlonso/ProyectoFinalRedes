#include "GameClient.h"

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

    initClient();
    socket.send(em, socket);

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
    myPlayer_= new Player(myNick_);
    myPlayer_->setTexture("Assets/player1.png");
    objMan_->addObject(myPlayer_);



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

        SDL_RenderCopy(game_->getRenderer(),game_->getBGTexture(),NULL,NULL);

        
        //Pintado de los GameObjects y mi jugador
        for (const auto& pair : objMan_->getObjects()) {
      
            GameObject * obj = pair.second;
            SDL_Rect location = {obj->getTransform().getX(),obj->getTransform().getY(),
                                obj->getDimensions().getX(),obj->getDimensions().getY()}; 
     
            SDL_RenderCopy(game_->getRenderer(),obj->getTexture(),NULL,&location);
       
        }
        //Pintado de otros jugadores (en este caso solo hay otro jugador y se podria pintar directamente, pero hago un bucle en caso de que hubiera mas)
        for (auto it = playersInfo_.begin(); it != playersInfo_.end(); ++it)
        {
            PlayerInfo p = (*it).second;
            SDL_Rect location = {p.posX_,p.posY_,p.w_,p.h_}; 
            
            SDL_RenderCopy(game_->getRenderer(),game_->getOtherPlayerTexture(),NULL,&location);
       
        }
        
        // Renderiza lo que hemos dibujado
        SDL_RenderPresent(game_->getRenderer());
        //SDL_UpdateWindowSurface(game_->getWindow());
   }
    
}
void GameClient::net_thread()
{

    while (true)
    {

        Message message;
        socket.recv(message);
        
        switch (message.type)
        {
            
            case Message::MessageType::LOGIN:
            {
                PlayerInfo p = message.playerInfo;

                if (message.nick!= myPlayer_->getNick())
                    playersInfo_[message.nick] = p;
                else
                {
                    myPlayer_->setTransform(p.posX_,p.posY_);
                }

                break;
            }
           
        }
       

    }
}