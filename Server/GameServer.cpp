#include "GameServer.h"
//#include "../NetUtils/Socket.h"

GameServer::GameServer(const char* s, const char* p) : socket(s, p)
{
        myState_.type=Message::MessageType::WAITING;
        socket.bind();
};
void GameServer::update(){

        while(!exit_){

        if(myState_.type==Message::MessageType::PLAYING){
            Message update;
            update.type=Message::MessageType::PLAYERINFO;

            //auto itPlayers=players.begin();
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                for(auto itPlayers = players.begin(); itPlayers != players.end(); itPlayers++)
                {
                    update.nick=(*itPlayers).first;
                    players[(*itPlayers).first].velY_+=gravity_;
                    players[(*itPlayers).first].posY_+=players[(*itPlayers).first].velY_;
                    update.playerInfo=players[(*itPlayers).first];

                    socket.send(update, *((*it).second.get()));
            
                }
                
            }
           
            
        }
}
        
        
}

void GameServer::do_messages()
{
    while (!exit_)
    {
        /*
         * NOTA: los clientes están definidos con "smart pointers", es necesario
         * crear un unique_ptr con el objeto socket recibido y usar std::move
         * para añadirlo al vector
         */

         //Recibir Mensajes en y en función del tipo de mensaje
         // Leer mensaje del cliente
         //Socket *client_socket;
         //ChatMessage msg;

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
                    info.velY_=0;
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
                    //Mensaje para avisar al otro cliente de los cambios de posicion
                    /*Message playerMoved;
                    playerMoved.nick=msg.nick;
                    playerMoved.message = msg.message;*/
               
                    if(msg.playerInfo.input_==Message::InputType::LEFT){
                     
                        players[msg.nick].posX_-=PLAYER_MOVEMENT_;

                    }
                    else if(msg.playerInfo.input_==Message::InputType::RIGHT){

                        players[msg.nick].posX_+=PLAYER_MOVEMENT_;
                    }

                    //playerMoved.playerInfo=players[playerMoved.nick];

                   //playerMoved.type=Message::MessageType::PLAYERINFO;

                    //Actualizamos la informacion correspondiente al cliente que se ha movido (ya que ha cambiado su posicion)
                    //Avisamos al resto de jugadores de este cambio en la posicion del contrario
                    /*auto itPlayers=players.begin();
                    for (auto it = clients.begin(); it != clients.end(); it++)
                    {
                        socket.send(playerMoved, *((*it).second.get()));
                        ++itPlayers;
                    }*/

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
                case Message::GAMEOVER:{
                  
                    Message over;
                    over.nick=msg.nick;
                    over.type=Message::MessageType::GAMEOVER;
                    myState_.type=Message::MessageType::GAMEOVER;
                    //Avisa a todos de que ha acabado el juego
                    std::cout<<"Fin de la partida\n";

                    for (auto it = clients.begin(); it != clients.end(); it++)
                    {
                        socket.send(over, *((*it).second.get()));
                    }

                    break;
                }
            }
        }

    }
}