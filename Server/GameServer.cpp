#include "GameServer.h"
#include "../NetUtils/Socket.h"
#include "../NetUtils/Message.h"

GameServer::GameServer(const char* s, const char* p) : socket(s, p)
{
        playerId_=0;
        players=(PlayerInfo*)malloc(sizeof(PlayerInfo)*2);
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

        if (msg.type == Message::LOGIN) {  // - LOGIN: Añadir al vector clients

            std::cout << msg.nick << " LOGIN\n";
            if (client_socket != nullptr) {

                std::unique_ptr<Socket> new_client(client_socket);
                PlayerInfo info;
                 //Siendo playerId la variable del servidor que controla el numero de clientes
                //Si es el primer jugador
                if(playerId_==0){
  
                    info.posX_=10;
                    info.posY_= 300;
                }
                else if(playerId_==1){ //es el segundo jugador
              
                    info.posX_=700;
                    info.posY_= 200;
                  
                }
                info.id_=playerId_;
                playerId_++;
  
                players[playerId_]=info;

                Message myMessage;
                myMessage.type=Message::PLAYERINFO;
                clients.push_back(std::move(new_client));
                myMessage.setPlayerInfo(info);
            
                std::cout<<"Estoy aqui\n";
                //Avisar a todos los jugadores conectados que ha entrado uno nuevo
                for (int i = 0; i < clients.size(); ++i) {
                    std::cout<<"Bucle 1: Mandando la info del que tiene id: "+std::to_string(players[i].id_)<<std::endl;
                    
                    socket.send(myMessage, *clients[i]);
                
                }
                //Avisar al que ha entrado de donde estan el resto
                for (int i = 0; i < clients.size(); ++i) {
                if (!((*clients[i]) == (*client_socket))) {
                        myMessage.setPlayerInfo(players[i]);
                        std::cout<<"Bucle 2: Mandando la info del que tiene id: "+std::to_string(players[i].id_)<<std::endl;
                        socket.send(myMessage, *clients[i]);
                    }
                }
            }
       
            
        }
        else if (msg.type == Message::LOGOUT) { // - LOGOUT: Eliminar del vector clients
            std::cout << msg.nick << " LOGOUT\n";

            for (int i = 0; i < clients.size(); ++i) {
                if ((*clients[i]) == (*client_socket)) {
                    clients.erase(clients.begin() + i);
                }
            }
        }
        else if (msg.type == Message::MESSAGE){ // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)

            std::cout << msg.nick << " MESSAGE\n";

            for (int i = 0; i < clients.size(); ++i) {
                if (!((*clients[i]) == (*client_socket))) {
                    socket.send(msg, *clients[i]);
                }
            }
        }

    }
}