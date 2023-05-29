#include "GameServer.h"
#include "../NetUtils/Socket.h"
#include "../NetUtils/Message.h"

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

        Socket* client_socket;
        Message msg;

        int client_fd = socket.recv(msg, client_socket);


        if (msg.type == Message::LOGIN) {  // - LOGIN: Añadir al vector clients

            std::cout << msg.nick << " LOGIN\n";
            if (client_socket != nullptr) {

                std::unique_ptr<Socket> new_client(client_socket);
                PlayerInfo info;
                info.id_=playerId_; //Siendo playerId la variable del servidor que controla el numero de clientes
                //Si es el primer jugador
                if(playerId_==0){
                    info.posX_=300;
                    info.posY_= 300;
                }
                else if(playerId_==1){ //es el segundo jugador
                    info.posX_=500;
                    info.posY_= 710;
                }
                msg.type=Message::PLAYERINFO;
                msg.setPlayerInfo(info);
                clients.push_back(std::move(new_client));
                socket.send(msg, *client_socket);
                playerId_++;

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