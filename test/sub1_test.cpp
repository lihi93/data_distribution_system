#include "dispatcher.hpp"
#include "comm_man.hpp"

#include "subscriber.hpp"



int main()
{
    Subscriber sub("127.0.0.1", 8080);
    sub.Subscribe("square");

    sleep (30);
    sub.StopRunning();
    return 0;
}