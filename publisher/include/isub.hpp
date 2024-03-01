#ifndef ISUB
#define ISUB

#include <string>
#include <netinet/in.h>

using std::string;

class Isub
{
public:
    Isub();
    virtual ~Isub();   
    virtual int Notify(string msg) = 0;
};

class UDPsub: public Isub
{
public:
    UDPsub(struct sockaddr_in sender_address);
    ~UDPsub();
    int Notify(const string msg);
private:
    struct sockaddr_in m_sub_addr;
    int m_socket;
};



#endif //ISUB