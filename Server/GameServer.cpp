#include "GameServer.h"
//#include "../NetUtils/Socket.h"
#include "../SDL_Utils/Vector2D.h"
GameServer::GameServer(const char* s, const char* p) : socket(s, p)
{
        myState_.type=Message::MessageType::WAITING;
        addPlatforms();
        socket.bind();
};
void GameServer::addPlatforms(){

    colMan_= CollisionManager();
    
    colMan_.addPlatforms(Vector2D(600,400));
    colMan_.addPlatforms(Vector2D(200,400));
    colMan_.addPlatforms(Vector2D(400,300));
    colMan_.addPlatforms(Vector2D(300,220));
    colMan_.addPlatforms(Vector2D(200,150));
    colMan_.addPlatforms(Vector2D(200,50));
    colMan_.addPlatforms(Vector2D(100,0));
    colMan_.addPlatforms(Vector2D(200,-50));
    colMan_.addPlatforms(Vector2D(400,-150));
    colMan_.addPlatforms(Vector2D(300,-250));

}
void GameServer::update(){

        while(!exit_){

        if(myState_.type==Message::MessageType::PLAYING){
            Message update;
            update.type=Message::MessageType::PLAYERINFO;

            //Aplicamos la gravedad
            for(auto itPlayers = players.begin(); itPlayers != players.end(); itPlayers++)
            {
                    update.nick=(*itPlayers).first;
                    players[(*itPlayers).first].velY_+=gravity_;
                    players[(*itPlayers).first].posY_+=players[(*itPlayers).first].velY_;
                    update.playerInfo=players[(*itPlayers).first];

                    for (auto it = clients.begin(); it != clients.end(); it++)
                    {
                        socket.send(update, *((*it).second.get()));
                
                    }
            
            }

            for(auto itPlayers = players.begin(); itPlayers != players.end(); itPlayers++)
            {
                 
                    Vector2D playerPos(players[(*itPlayers).first].posX_,players[(*itPlayers).first].posY_);
                    Vector2D playerDim(players[(*itPlayers).first].w_,players[(*itPlayers).first].h_);

                    if(colMan_.checkPlayerPlatformsCollisions(players[(*itPlayers).first].velY_,playerPos,playerDim,Vector2D(platW_,platH_))){

                        players[(*itPlayers).first].velY_=jumpVel_;
                    }    
                    if(players[(*itPlayers).first].posY_< 0){
                        Message win;
                        win.type=Message::MessageType::GAMEOVER;
                        myState_.type=Message::MessageType::GAMEOVER;

                        win.nick=(*itPlayers).first;
                        for (auto it = clients.begin(); it != clients.end(); it++)
                        {
                            socket.send(win, *((*it).second.get()));
                
                        }
                    }

                            
            }
            
  
        }
            
    }
}
        
void GameServer::do_messages()
{
    while (!exit_)
    {

        Socket* client_socket=new Socket(socket);
        Message msg;

        //Esperamos recibir un mensaje de cualquier socket
        if (socket.recv(msg, client_socket) == -1)
        {
            std::cout << "Error al recibir el mensaje\n";
        }
        else {

            switch(msg.type){
                case Message::LOGIN:{
                    
                    if(firstName_==""){
                        firstName_=msg.nick;
                    }
                    else{
                        if(msg.nick==firstName_){
                            std::cout<<"Ese nick ya está en uso, inténtelo de nuevo"<<std::endl;
                           
                            Message retry;
                            retry.type=Message::MessageType::WRONG_NAME;
                            socket.send(retry,*client_socket);
                            break;
                        }
                    }
                    std::cout << msg.nick << " LOGIN\n";
                    std::unique_ptr<Socket> new_client(client_socket);
                
                    clients[msg.nick]=std::move(new_client);
                    PlayerInfo info;
                    info.posX_ = rand()%(670-50 + 1) + 50;
                    info.posY_= rand()%(430-50 + 1) + 50;
                    info.velY_=0.0f;
                    info.w_=50;
                    info.h_=50;
                    players[msg.nick]=info;
                    Message newPlayer;
                    newPlayer.type= Message::MessageType::INIPLAYER;
                    newPlayer.nick=msg.nick;
                    newPlayer.playerInfo=players[msg.nick];

                    //Vamos a enviar un mensaje al cliente con su informacion de inicio
                    socket.send(newPlayer, *client_socket);

                    auto itPlayers=players.begin();
                    for (auto it = clients.begin(); it != clients.end(); it++)
                    {
                        if((*itPlayers).first!=newPlayer.nick){
                        socket.send(newPlayer, *((*it).second.get()));
                        }
                        ++itPlayers;
                    }
            
                    //Avisar de la posicion del contrario
                    for (auto it = players.begin(); it != players.end(); ++it)
                    {   
                        //Si tiene un nick distinto al mio (es otro jugador) mandame su informacion
                        if ((*it).first != newPlayer.nick)
                        {
                            newPlayer.nick=(*it).first;
                            newPlayer.playerInfo=(*it).second;
                            socket.send(newPlayer,*client_socket);
                        }
                   
                    }
                    //Si solo se ha conectado un jugador
                    if(clients.size() <= 1){
                        Message waiting;
                        waiting.type=Message::MessageType::WAITING;
                        std::cout<<"Esperando otro jugador...\n";
                        //Avisamos a ese jugador de que espere
                        socket.send(waiting,*client_socket);

                    }
                    else{
                        Message ready;
                        ready.type=Message::MessageType::PLAYING;
                        myState_.type=Message::MessageType::PLAYING;
                        //Avisa a todos de que podemos empezar
                        std::cout<<"Ya hay dos jugadores, empecemos!\n";

                        for (auto it = clients.begin(); it != clients.end(); it++)
                        {
                            socket.send(ready, *((*it).second.get()));
                        }
                    }
                    break;

                
                }
                case Message::INPUT:
                {

                    if(msg.playerInfo.input_==Message::InputType::LEFT){
                     
                        players[msg.nick].posX_-=PLAYER_MOVEMENT_;

                    }
                    else if(msg.playerInfo.input_==Message::InputType::RIGHT){

                        players[msg.nick].posX_+=PLAYER_MOVEMENT_;
                    }

                    break;
                }
                case Message::LOGOUT:{
                    std::cout << msg.nick << " LOGOUT\n";
                    auto itPlayers=players.begin();
                    for (auto it = clients.begin(); it != clients.end(); it++)
                    {
                        if((*itPlayers).first==msg.nick){
                            clients.erase(it);
                            players.erase(itPlayers);
                            break;
                        }
                        ++itPlayers;
                    }
                    //Se han ido todos los jugadores
                    if(clients.size()<1){
                        exit_=true;
                    }
                 
                    break;
                }
                
            }
        }

    }
}