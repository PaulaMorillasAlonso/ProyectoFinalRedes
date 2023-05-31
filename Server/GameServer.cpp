#include "GameServer.h"
//#include "../NetUtils/Socket.h"

GameServer::GameServer(const char* s, const char* p) : socket(s, p)
{
       
        //players=(PlayerInfo*)malloc(sizeof(PlayerInfo)*2);
        socket.bind();
};

void GameServer::do_messages()
{
    while (true)
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
                    
                    std::cout << msg.nick << " LOGIN\n";
                
                    std::unique_ptr<Socket> new_client(client_socket);
                
                    clients[msg.nick]=std::move(new_client);
                    PlayerInfo info;
                    info.posX_ = rand()%(670-50 + 1) + 50;
                    info.posY_= rand()%(430-50 + 1) + 50;
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
                    break;

                
                }
                case Message::INPUT:
                {
                    if(msg.playerInfo.input_==Message::LEFT){
                        std::cout<<"Te has movido a la izquierda\n";
                        
                    }
                    else if(msg.playerInfo.input_==Message::RIGHT){
                        std::cout<<"Te has movido a la derecha\n";
                    }
                    break;
                }
                case Message::LOGOUT:{
                    std::cout << msg.nick << " LOGOUT\n";

                    /*for (int i = 0; i < clients.size(); ++i) {
                        if ((*clients[i]) == (*client_socket)) {
                        clients.erase(clients.begin() + i);
                    }
                     }*/
                    break;
                }
                case Message::MESSAGE:{
                    std::cout << msg.nick << " MESSAGE\n";

                    /*for (int i = 0; i < clients.size(); ++i) {
                    if (!((*clients[i]) == (*client_socket))) {
                        socket.send(msg, *clients[i]);
                    }
                    }*/
                    break;
                }

            }
        }

    }
}