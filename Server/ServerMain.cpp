#include "GameServer.h"
int main(int argc, char **argv)
{
    GameServer es(argv[1], argv[2]);

    es.do_messages();
    //Chequea el estado del servidor
    return 0;
}
