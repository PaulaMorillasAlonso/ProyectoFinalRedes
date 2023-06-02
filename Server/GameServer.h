
#include <string>
#include <unistd.h>
#include <string.h>
#include <map>
#include <thread>
#include <memory>
#include "../NetUtils/Socket.h"
#include "../NetUtils/Message.h"
#include "../NetUtils/CollisionManager.h"

class GameServer
{
public:
    GameServer(const char* s, const char* p);

    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void do_messages();
    void update();
    void addPlatforms();
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
    

    float gravity_=0.000002f;
    float jumpVel_=-0.025f;
    const float PLAYER_MOVEMENT_=5.0f;
    Message myState_;
    Socket socket;
    std::string firstName_="";
    bool exit_=false;
    CollisionManager colMan_;
    int platW_=150;
    int platH_=30;

};
