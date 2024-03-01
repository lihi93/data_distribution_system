#ifndef COMM_MAN
#define COMM_MAN

#include <vector>
#include <thread> //thread

#include "dispatcher.hpp"
#include "isub.hpp"

using std::vector;
using std::thread;

class CommMan
{
public:
    CommMan(Dispatcher *disp, const char *ip_addr, int port);
    ~CommMan();
    void StopComm();

private:
    void Listening();
    void Stop();

    Dispatcher *m_disp;
    int m_socket;
    thread m_listener;
    thread m_stop;
};



#endif //COMM_MAN