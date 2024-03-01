#include "subscriber.hpp"
#include "../../publisher/include/shape.hpp"
#include <string>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread> //std::thread
#include <unistd.h> //sleep
#include <arpa/inet.h> //inet_addr

int main()
{
    int soc= socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234); 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t len = sizeof(addr);

    shape_data_t shape;
    shape.alt = 1.0;
    shape.lat = 2.1;
    shape.color = "green";
    shape.lon = 3.2;
    shape.name = "circle";
    shape.size = 4;
    char data[1024] = "hey Yuval";
    while (true)
    {

        if (-1 == sendto(soc, data, sizeof(shape), 0, (const sockaddr*)&addr, len))
        {
            perror("sendto");
        }
    }

    return 0;
}