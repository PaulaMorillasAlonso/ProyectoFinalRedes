
#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <thread>
#include <memory>
#include "../NetUtils/Socket.h"

class GameServer
{
public:
    GameServer(const char* s, const char* p) : socket(s, p)
    {
        playerId_=0;
        socket.bind();
    };

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
    std::vector<std::unique_ptr<Socket>> clients;

    /**
     * Socket del servidor
     */
    int playerId_;
    Socket socket;

};
