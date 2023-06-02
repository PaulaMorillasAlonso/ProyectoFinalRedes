#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <thread>
#include <memory>

#include "../NetUtils/Serializable.h"
#include "../NetUtils/Socket.h"

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
struct PlayerInfo{

    float posX_;
    float posY_;
    int input_;
    float velY_;
    int w_;
    int h_;
};
class Message : public Serializable
{
public:

    enum MessageType
    {
        LOGIN = 0,
        LOGOUT = 1,
        INIPLAYER=2,
        INPUT=3,
        WAITING=4,
        PLAYING=5,
        GAMEOVER=6,
        WRONG_NAME=7,
        PLAYERINFO=8

 
    };

    enum InputType{
        NONE=0,
        LEFT=1,
        RIGHT=2
    };

    Message() {};

    Message(const std::string& n, const std::string& m) :nick(n), message(m) {};

    void to_bin();

    int from_bin(char* bobj);
    
    uint8_t type;

    PlayerInfo playerInfo;
    std::string nick;
    std::string message;
};

