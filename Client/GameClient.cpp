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
    myPlayer_->setKeys(SDL_SCANCODE_A,SDL_SCANCODE_D);
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
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning_= false;
                logout();
            }
            else{
                SDL_Scancode pressedKey;
                pressedKey= myPlayer_->handleInput(event);
                if(pressedKey!=SDL_SCANCODE_UNKNOWN){
                    updateMyInfo();
                    Message msg;
                    msg.nick=myNick_;
                    msg.type=Message::MessageType::INPUT;

                    if(pressedKey==SDL_SCANCODE_A){ //Se mueve a izq

                        msg.playerInfo.input_= Message::LEFT;
                        std::cout<<"Oye server me he movido hacia la izquierda\n";
                    }
                    else if(pressedKey==SDL_SCANCODE_D){ //Se mueve a der

                        msg.playerInfo.input_= Message::RIGHT;
                        std::cout<<"Oye server me he movido hacia la derecha\n";

                    }
                    msg.playerInfo=playersInfo_[myNick_];
                    socket.send(msg, socket);
                }
                

            }
            
        }
        
        //Message msg(nick, buffer);
        //msg.type = Message::MESSAGE;
        //socket.send(msg, socket);
        
}
void GameClient::render() const{


        //Pintado de fondo
        SDL_SetRenderDrawColor(game_->getRenderer(),0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(game_->getRenderer());

        SDL_RenderCopy(game_->getRenderer(),game_->getBGTexture(),NULL,NULL);

        
        //Pintado de los GameObjects y jugadores
        for (const auto& pair : objMan_->getObjects()) {
      
            GameObject * obj = pair.second;
            SDL_Rect location = {obj->getTransform().getX(),obj->getTransform().getY(),
                                obj->getDimensions().getX(),obj->getDimensions().getY()}; 
     
            SDL_RenderCopy(game_->getRenderer(),obj->getTexture(),NULL,&location);
       
        }

        // Renderiza lo que hemos dibujado
        SDL_RenderPresent(game_->getRenderer());
        SDL_UpdateWindowSurface(game_->getWindow());
   
    
}
void GameClient::net_thread()
{

    while (true)
    {
        Message message;
        socket.recv(message);
        
        switch (message.type)
        {
            
            case Message::MessageType::INIPLAYER:
            {
                PlayerInfo p = message.playerInfo;

                if (message.nick!= myPlayer_->getNick())
                {
                    playersInfo_[message.nick] = p;
                    Player *player= new Player(message.nick);
                    player->setTexture("Assets/player2.png");
                    player->setTransform(message.playerInfo.posX_,message.playerInfo.posY_);
                    objMan_->addObject(player);

                    std::cout<<"La otra posicion X es: "<<std::to_string(p.posX_)<<"\n";
                    std::cout<<"La otra posicion Y es: "<<std::to_string(p.posY_)<<"\n";
                }
                else
                {
                    myPlayer_->setTransform(p.posX_,p.posY_);

                    PlayerInfo myInfo;
        
                    myInfo.posX_=myPlayer_->getTransform().getX();
                    myInfo.posY_=myPlayer_->getTransform().getY();
                    playersInfo_[myNick_]=myInfo;
                    std::cout<<"Mi posicion X es: "<<std::to_string(p.posX_)<<"\n";
                    std::cout<<"Mi posicion Y es: "<<std::to_string(p.posY_)<<"\n";

                }

                break;
            }
           
        }
       

    }
}
void GameClient::run(){
    while(gameIsRunning_){
        render();
        input_thread();
    }
    
}
void GameClient::updateMyInfo(){

    //Actualiza la informacion que le voy a enviar al servidor
    PlayerInfo myInfo;
    
    myInfo.posX_=myPlayer_->getTransform().getX();
    myInfo.posY_=myPlayer_->getTransform().getY();

    playersInfo_[myNick_].posX_=myInfo.posX_;
    playersInfo_[myNick_].posY_=myInfo.posY_;
}