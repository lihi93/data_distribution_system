#include <iostream>
#include "comm_man.hpp"
#include "dispatcher.hpp"
#include <unistd.h>
int main (void)
{
    Dispatcher *m_disp = new Dispatcher();
    CommMan cm(m_disp, nullptr, 8080);
    int num = 50;
    sleep(5);
    while (true)
    {
        m_disp->Notify("square", "hey there, this is a square");
        //sleep(1);

        m_disp->Notify("circle", "hey there, this is a circle");
        
    }

    while(true);
    delete m_disp;
    return 0;
}