#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <thread>
#include <memory>

#include "../NetUtils/Serializable.h"
#include "../NetUtils/Socket.h"
#include "PlayerInfo.h"
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 *  Mensaje del protocolo de la aplicación de Chat
 *
 *  +-------------------+
 *  | Tipo: uint8_t     | 0 (login), 1 (mensaje), 2 (logout)
 *  +-------------------+
 *  | Nick: char[8]     | Nick incluido el char terminación de cadena '\0'
 *  +-------------------+
 *  |                   |
 *  | Mensaje: char[80] | Mensaje incluido el char terminación de cadena '\0'
 *  |                   |
 *  +-------------------+
 *
 */
class Message : public Serializable
{
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t)+ sizeof(PlayerInfo);

    enum MessageType
    {
        LOGIN = 0,
        PLAYERINFO=1,
        MESSAGE = 2,
        LOGOUT = 3
    };

    Message() {};

    Message(const std::string& n, const std::string& m) :nick(n), message(m) {};

    void to_bin();

    int from_bin(char* bobj);
    
    void setPlayerInfo(const PlayerInfo& info){
        playerInfo= info;
        std::cout<<"PlayerInfo:"<<playerInfo.posX_<<"\n";
    }

    uint8_t type,id;

    PlayerInfo playerInfo;
    std::string nick;
    std::string message;
};

