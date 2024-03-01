#include <sys/types.h> //recv
#include <sys/socket.h> //recv
#include <netinet/in.h> // sockaddr_in
#include <cstring> // strlen
#include <unistd.h> //close
#include <system_error> //system_error

#include "isub.hpp"

Isub::Isub(){}
Isub::~Isub(){}

UDPsub::UDPsub(struct sockaddr_in sub_addr):
    m_sub_addr(sub_addr)
{
    memcpy(&m_sub_addr, &sub_addr, sizeof(sub_addr));
    if(-1 == (m_socket = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        throw std::system_error(errno, std::system_category(), "Failed to open socket");
    }
}

UDPsub::~UDPsub()
{
    close(m_socket);
}

int UDPsub::Notify(const string msg)
{
    const char *message = msg.c_str();
    socklen_t len = sizeof(m_sub_addr);
    return sendto(m_socket, message, strlen(message) + 1, 0, (const struct sockaddr*)&m_sub_addr, len);
}