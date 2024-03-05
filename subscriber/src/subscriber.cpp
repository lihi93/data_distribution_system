#include <unistd.h> //close
#include <iostream> //close
#include <cstring> //close
#include <sstream> //iss
#include <arpa/inet.h> //inet_addr

#include "subscriber.hpp"

/******************************** Ctor / Dtor ***************************************/

Subscriber::Subscriber(const char *server_ip, const int server_port): is_listening(true), server_addr({0})
{
    if (-1==(m_socket = socket(AF_INET, SOCK_DGRAM, 0))) //except
    {
        throw std::system_error(errno, std::system_category(), "Failed to bind socket");
    }
    
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    
    listening_thread = std::thread(&Subscriber::ListeningThread, this);
}

Subscriber::~Subscriber()
{
    close(m_socket);
    listening_thread.join();
}


/******************************** public funcs ***************************************/


void Subscriber::Subscribe(string shape)
{
    if (-1 == sendto(m_socket, shape.c_str(), shape.size(), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)))
    {
        throw std::system_error(errno, std::system_category(), "sendto failed");
    }
}

void Subscriber::StopRunning()
{
    shutdown(m_socket, SHUT_RD);
}


/******************************** inner funcs ***************************************/

void Subscriber::ListeningThread()
{
    while (true)
    {
        char recv_message[1024];
        int stat = recv(m_socket, recv_message, sizeof(recv_message), 0);
        if (-1 == stat)
        {
            throw std::system_error(errno, std::system_category(), "recv Failed");
        }
        else if (0 == stat)
        {
            break;
        }

        this->AtNotify(recv_message);
    }
}

void Subscriber::AtNotify(string msg)
{
    shape_data_t result = StringToStruct(msg);

    std::cout << "shape: "<< result.name << std::endl;
    std::cout << "color: "<< result.color << std::endl;
    std::cout << "size: "<< result.size << std::endl;
    std::cout << "lat: "<< result.lat << std::endl;
    std::cout << "lon: "<< result.lon << std::endl;
    std::cout << "alt: "<< result.alt << std::endl;  
}





