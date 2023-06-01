#include "GameServer.h"
int main(int argc, char **argv)
{
    GameServer es(argv[1], argv[2]);

    std::thread net_thread([&es](){ es.do_messages(); });

     //update de la gravedad
    es.update();
   
    return 0;
}
