/*
Subscribers can be either on the same machine with the sever or on a 
    different one. if it is on the same machine, Ctor's parameter server_port 
    should be the server's port. If it is on a different machine the port
    should be the server's broadcast port and the server_ip should be nullptr.
*/

#ifndef SUBSCRIBER
#define SUBSCRIBER

#include <string>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread> //std::thread
#include <unistd.h> //sleep

#include "shape.hpp"

using std::string;

class Subscriber
{
public:
    Subscriber(const char *server_ip, const int server_port);
    ~Subscriber(); 
    void Subscribe(string shape);

private:
    void Connecting(); //listening to broadcasting, sending confirmation(shape interest)
    void Listening(); //selector
    void AtNotify(string msg);
    void ListeningThread(); //selector

    char server_ip;
    int server_port;
    int m_socket;
    bool is_listening;

    struct sockaddr_in server_addr;
    socklen_t m_len;

    std::thread listening_thread;

};


#endif //SUBSCRIBER