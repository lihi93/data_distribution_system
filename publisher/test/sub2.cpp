#include <iostream>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
int main(void)
{
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); 
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    const char* message = "circle";
    ssize_t bytesSent = sendto(clientSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    char buff[50];
    while (true)
    {
        socklen_t len = sizeof(serverAddress);
        recvfrom(clientSocket, buff, strlen(buff) + 1, 0, (struct sockaddr *)&serverAddress ,&len );
        std::cout << buff << std::endl;
    }
    
    return 0;
}