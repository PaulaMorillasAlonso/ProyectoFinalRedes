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

    //Borramos la ventana
    game_->destroyWindow();

    //Liberamos la memoria
    delete myPlayer_;
    delete otherPlayer_;
    delete objMan_;
    delete game_;
}

void GameClient::input_thread()
{
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(canExit_)
            {
                //Si el jugador sale por si mismo o si han pasado 5 segundos hace logout
                float currTime=SDL_GetTicks()/1000.f;
                if(event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE || currTime-logoutDelay_ > 5 ){ 
                    gameIsRunning_= false;
                    logout();
                    break;
                }
            }
            else{
                
                SDL_Scancode pressedKey;
                if(!waitingForOther_){
                    pressedKey= myPlayer_->handleInput(event);
                    if(pressedKey!=SDL_SCANCODE_UNKNOWN){

                        //Actualiza la informacion que el cliente tiene sobre su jugador
                        updateMyInfo();
                        //Envia esta informacion al servidor, que podra avisar al resto de jugadores
                        Message msg;
                        msg.nick=myNick_;
                        msg.type=Message::MessageType::INPUT;
                        msg.playerInfo=playersInfo_[myNick_];
                        socket.send(msg, socket);
                    }
                }
                
            }
            
        }
        
}
void GameClient::render() const{


        //Pintado de fondo
        if(waitingForOther_){
            SDL_RenderCopy(game_->getRenderer(),game_->getWaitingTexture(),NULL,NULL);
        }
        else{

            SDL_RenderCopy(game_->getRenderer(),game_->getBGTexture(),NULL,NULL);

            //Pintado de los GameObjects y jugadores
            for (const auto& pair : objMan_->getObjects()) {
      
                GameObject * obj = pair.second;
                SDL_Rect location = {obj->getTransform().getX(),obj->getTransform().getY(),
                                obj->getDimensions().getX(),obj->getDimensions().getY()}; 
     
                SDL_RenderCopy(game_->getRenderer(),obj->getTexture(),NULL,&location);
       
            }
        }


        // Renderiza lo que hemos dibujado
        SDL_RenderPresent(game_->getRenderer());
        SDL_UpdateWindowSurface(game_->getWindow());
   
    
}
void GameClient::update(){

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
                    otherPlayer_= new Player(message.nick);
                    otherPlayer_->setTexture("Assets/player2.png");
                    otherPlayer_->setTransform(message.playerInfo.posX_,message.playerInfo.posY_);
                    objMan_->addObject(otherPlayer_);
                }
                else
                {
                    myPlayer_->setTransform(p.posX_,p.posY_);

                    PlayerInfo myInfo;
                    myInfo.posX_=myPlayer_->getTransform().getX();
                    myInfo.posY_=myPlayer_->getTransform().getY();
                    playersInfo_[myNick_]=myInfo;

                }

                break;
            }
            case Message::MessageType::INPUT:{

                //Si otro jugador se ha movido, actualizo su información

                if (message.nick!= myPlayer_->getNick())
                {
                    otherPlayer_->setTransform(message.playerInfo.posX_,message.playerInfo.posY_);
                }
                break;
            }
            case Message::MessageType::WAITING:{

                break;
            }
            case Message::MessageType::PLAYING:{

                gameIsRunning_=true;
                waitingForOther_=false;
                break;
            }
            case Message::MessageType::GAMEOVER:{
                //Asi evitamos que salga durante la partida
                canExit_=true;
                logoutDelay_=SDL_GetTicks()/1000.f;
                break;
            }
        }
       
    }
}
void GameClient::run(){
    while(gameIsRunning_||waitingForOther_){
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

    /*Prueba para comprobar si funcionaba el cambio a gameover
    if(myInfo.posX_<-10){
        std::cout<<"He perdido\n";
        Message final;
        final.type=Message::MessageType::GAMEOVER;
        socket.send(final,socket);
    }*/
}