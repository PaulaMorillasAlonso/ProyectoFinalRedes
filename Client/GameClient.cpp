#include "GameClient.h"
#include "../NetUtils/Message.h"
void GameClient::login()
{
    std::string msg;
    Message em(nick, msg);
    em.type = Message::LOGIN;

    socket.send(em, socket);

}

void GameClient::logout()
{
    std::string msg;

    Message em(nick, msg);
    em.type = Message::LOGOUT;

    socket.send(em, socket);

}

void GameClient::input_thread()
{
    while (true)
    {
        char buffer[Message::MESSAGE_SIZE];
        std::cin.getline(buffer, Message::MESSAGE_SIZE);
        if (strcmp(buffer, "q") == 0) {
            logout();
            break;
        }
        else {
            Message msg(nick, buffer);
            msg.type = Message::MESSAGE;
            socket.send(msg, socket);
        }
    }
}

void GameClient::net_thread()
{
    while (true)
    {
        Message msg;
        socket.recv(msg);
        std::cout << msg.nick << ": " << msg.message << "\n";

    }
}