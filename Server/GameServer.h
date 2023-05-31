
#include <string>
#include <unistd.h>
#include <string.h>
#include <map>
#include <thread>
#include <memory>
#include "../NetUtils/Socket.h"
#include "../NetUtils/Message.h"

class GameServer
{
public:
    GameServer(const char* s, const char* p);

    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void do_messages();

private:
    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::map<std::string,std::unique_ptr<Socket>> clients;
    std::map<std::string, PlayerInfo> players;
    /**
     * Socket del servidor
     */
    Message myState_;
    Socket socket;


};
