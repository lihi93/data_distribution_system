#include <sys/types.h> //recv
#include <sys/socket.h> //recv
#include <netinet/in.h> // sockaddr_in
#include <cstring> // memset
#include <unistd.h> //close
#include <iostream>
#include <arpa/inet.h> //inet_addr
#include <memory> //shared_ptr

#include "comm_man.hpp"

CommMan::CommMan(Dispatcher *disp, const char *ip_addr, int port):
    m_disp(disp)
{
    if (-1 == (m_socket = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        throw std::system_error(errno, std::system_category(), "Failed to open socket");
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); 
    addr.sin_addr.s_addr = inet_addr(ip_addr);
    
    if (-1 == bind(m_socket, (struct sockaddr*)&addr, sizeof(addr)))
    {
        throw std::system_error(errno, std::system_category(), "Failed to bind socket");
    }
    /* establishing listening thread */
    m_listener = thread(&CommMan::Listening, this); 
}

CommMan::~CommMan()
{
    m_listener.join();
    m_stop.join();    
}

void CommMan::Listening()
{
    while (true)
    {
        char shape_msg[1024];

        struct sockaddr_in sender_address;
        memset(&sender_address, 0, sizeof(sender_address));
        socklen_t sender_address_len = sizeof(sender_address);

        /*listening to messages from subs*/
        if (-1 == recvfrom(m_socket, shape_msg, sizeof(shape_msg), 0, (struct sockaddr *)&sender_address, &sender_address_len))
        {
            throw std::system_error(errno, std::system_category(), "recvfrom Failed");
        }
        
        std::shared_ptr<Isub> new_sub = std::make_shared<UDPsub>(sender_address);
        string shape(shape_msg);

        /* registering new_sub to dispatcher with its
            shape of interest */
        m_disp->Register(shape, new_sub);
    }
}


void CommMan::StopComm()
{
    m_stop = thread(&CommMan::Stop, this); //except
}

void CommMan::Stop()
{
    close(m_socket);
}
