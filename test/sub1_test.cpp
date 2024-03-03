#include "dispatcher.hpp"
#include "comm_man.hpp"

#include "subscriber.hpp"



int main()
{
    Subscriber sub("127.0.0.1", 8080);
    sub.Subscribe("square");

    while (1)
    {
        sleep (1000);
    }
    return 0;
}