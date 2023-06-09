#include "GameClient.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../NetUtils/SDLGame.h"
#include "Game/Player.h"
#include "../NetUtils/ObjectManager.h"
#include "Game/PlatformManager.h"
#include "Game/CameraManager.h"

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
    platMan_= new PlatformManager();
    camMan_= new CameraManager();

    camMan_->setWindowHeight(480);

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
    //collMan_->setPlayer(myPlayer_);
    camMan_->addPlayer(myPlayer_);


    // Test Platform
    int testPlatX = 600;
    int testPlatY = 400;
    Platform* p = platMan_->createPlatform(Vector2D(testPlatX, testPlatY));
    objMan_->addObject(p);
    camMan_->addScrollingObject(p);

    // Platforms
    Platform* p1 = platMan_->createPlatform(Vector2D(200, 400));
    objMan_->addObject(p1);
    camMan_->addScrollingObject(p1);

    Platform* p2 = platMan_->createPlatform(Vector2D(400, 300));
    objMan_->addObject(p2);
    camMan_->addScrollingObject(p2);

    Platform* p3 = platMan_->createPlatform(Vector2D(300, 220));
    objMan_->addObject(p3);
    camMan_->addScrollingObject(p3);

    Platform* p4 = platMan_->createPlatform(Vector2D(200, 150));
    objMan_->addObject(p4);
    camMan_->addScrollingObject(p4);

    Platform* p5 = platMan_->createPlatform(Vector2D(200, 50));
    objMan_->addObject(p5);
    camMan_->addScrollingObject(p5);

    Platform* p6 = platMan_->createPlatform(Vector2D(100, 0));
    objMan_->addObject(p6);
    camMan_->addScrollingObject(p6);

    Platform* p7 = platMan_->createPlatform(Vector2D(200, -50));
    objMan_->addObject(p7);
    camMan_->addScrollingObject(p7);

    Platform* p8 = platMan_->createPlatform(Vector2D(400, -150));
    objMan_->addObject(p8);
    camMan_->addScrollingObject(p8);

    Platform* p9 = platMan_->createPlatform(Vector2D(300, -250));
    objMan_->addObject(p9);
    camMan_->addScrollingObject(p9);

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
                if(event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE || currTime-logoutDelay_ > timeUntilLogout_ ){ 
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

                        //Envia esta informacion al servidor, que podra avisar al resto de jugadores
                        Message msg;
                        msg.nick=myNick_;
                        msg.type=Message::MessageType::INPUT;

                        if(pressedKey==SDL_SCANCODE_A){ //Movimiento izquierda
                           
                            playersInfo_[myNick_].input_=Message::InputType::LEFT;
                        }
                        else if (pressedKey==SDL_SCANCODE_D){
                         

                            playersInfo_[myNick_].input_=Message::InputType::RIGHT;
                        }
                        msg.message="move";
                        msg.playerInfo=playersInfo_[myNick_];
                        socket.send(msg, socket);
                    }
                
                }
                
            }
            
        }
        
}
void GameClient::render() const{


        //Pintado de fondo

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
            case Message::MessageType::WRONG_NAME:{
                //Mensaje que solo se manda en caso de que un segundo jugador tenga el mismo nombre que el primero
                mustExit_=true;
                break;
            }
            case Message::MessageType::INIPLAYER:
            {
                PlayerInfo p = message.playerInfo;
              
                if (message.nick!= myPlayer_->getNick())
                {
                    playersInfo_[message.nick] = p;
                    otherPlayer_= new Player(message.nick);
                    otherPlayer_->setTexture("Assets/player2.png");
                    otherPlayer_->setDimensions(message.playerInfo.w_,message.playerInfo.h_);
                    otherPlayer_->setTransform(message.playerInfo.posX_,message.playerInfo.posY_);
                    objMan_->addObject(otherPlayer_);
                    camMan_->addPlayer(otherPlayer_);
                }
                else
                {   
                    myPlayer_->setDimensions(message.playerInfo.w_,message.playerInfo.h_);
                    myPlayer_->setTransform(p.posX_,p.posY_);

                    PlayerInfo myInfo;
                    myInfo.posX_=myPlayer_->getTransform().getX();
                    myInfo.posY_=myPlayer_->getTransform().getY();
                    playersInfo_[myNick_]=myInfo;

                }

                break;
            }
            case Message::MessageType::INPUT:{

                if (message.message == "jump"){
                    // std::cout << "Overlap!\n";
                    if (message.nick!= myPlayer_->getNick())
                    {
                        otherPlayer_->setVelY(otherPlayer_->getJumpVel());
                    }
                    else {
                        myPlayer_->setVelY(myPlayer_->getJumpVel());
                    }
                }

                //Si otro jugador se ha movido, actualizo su información
                if (message.nick!= myPlayer_->getNick())
                {
                    otherPlayer_->setTransform(message.playerInfo.posX_,message.playerInfo.posY_);
                }
                break;
            }
            case Message::MessageType::WAITING:{
                std::cout <<"Estoy esperando a otros jugadores\n";
                break;
            }

            case Message::MessageType::PLAYING:{

                gameIsRunning_=true;
                waitingForOther_=false;
                
                break;
            }
            case Message::MessageType::GAMEOVER:{
                //Asi evitamos que salga durante la partida

                if (message.nick == myPlayer_->getNick())
                {
                    std::cout << "He ganado\n";
                }
                else {
                    std::cout << "He perdido\n";
                }

                canExit_=true;
                logoutDelay_=SDL_GetTicks()/1000.f;
       
                break;
            }
            case Message::MessageType::PLAYERINFO:{

                if (message.nick!= myPlayer_->getNick())
                    {
                        otherPlayer_->setTransform(message.playerInfo.posX_,message.playerInfo.posY_);
                        otherPlayer_->setVelY(message.playerInfo.velY_);

                    }
                    else {
                        myPlayer_->setTransform(message.playerInfo.posX_,message.playerInfo.posY_);
                        myPlayer_->setVelY(message.playerInfo.velY_);
                    }
                camMan_->scrollY(message.playerInfo.scrollY_);
                    
                break;
            }
        }
       
    }
}
void GameClient::run(){
    while((gameIsRunning_||waitingForOther_) && !mustExit_){
        render();
        if(!waitingForOther_){
            //updateCamera();
            input_thread();

        }
    }
    
}
