#include "Message.h"
#include <string>


static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t)+ sizeof(PlayerInfo);

void Message::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);

    //Serializar los campos type, nick, message y PlayerInfo en el buffer _data
    char* tmp = _data;
    memcpy(tmp, &type, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    memcpy(tmp, nick.c_str(), sizeof(char) * 8);
    tmp += sizeof(char) * 8;
    memcpy(tmp, message.c_str(), sizeof(char) * 80);
    tmp+=sizeof(char)*80;
    memcpy(tmp, &playerInfo, sizeof(PlayerInfo));

}

int Message::from_bin(char* bobj)
{
    alloc_data(MESSAGE_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MESSAGE_SIZE);
    char* tmp = _data;

    //Reconstruir la clase usando el buffer _data
    memcpy(&type, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    char nick_buff[9] = { 0 };
    memcpy(nick_buff, tmp, sizeof(char) * 8);
    nick = std::string(nick_buff);
    tmp += sizeof(char) * 8;
    char m_buff[81] = { 0 };
    memcpy(m_buff, tmp, sizeof(char) * 80);
    message = std::string(m_buff);
    tmp += sizeof(char) * 80;
    memcpy(&playerInfo,tmp,sizeof(PlayerInfo));

    return 0;
}



