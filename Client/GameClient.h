#include <thread>
#include <memory>
#include <vector>
#include <string>
#include "../NetUtils/Socket.h"
#include "../NetUtils/SDLGame.h"
class GameClient
{
public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    GameClient(const char* s, const char* p, const char* n) :socket(s, p),
        nick(n) {};

    /**
     *  Envía el mensaje de login al servidor
     */
    void login();

    /**
     *  Envía el mensaje de logout al servidor
     */
    void logout();

    /**
     *  Rutina principal para el Thread de E/S. Lee datos de STDIN (std::getline)
     *  y los envía por red vía el Socket.
     */
    void input_thread();

    /**
     *  Rutina del thread de Red. Recibe datos de la red y los "renderiza"
     *  en STDOUT
     */
    void net_thread();
    /*
    Crea una pantalla de sdl para renderizado de tamaño w * h
    */
    void initClient(int w,int h);
    void render() const;

private:

    SDLGame* game_;
    /**
     * Socket para comunicar con el servidor
     */
    Socket socket;

    /**
     * Nick del usuario
     */
    std::string nick;

    std::vector<std::thread> threads;

};