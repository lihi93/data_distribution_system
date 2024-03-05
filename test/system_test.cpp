#include <unistd.h>
#include <iostream>
#include <unistd.h>
#include "dispatcher.hpp"
#include "comm_man.hpp"
#include "shape_gener.hpp"
#include "shape.hpp"

int main()
{
    Dispatcher disp;
    CommMan comm(disp, "127.0.0.1", 8080);
    ShapeGenerator s_g(disp);
    
    Circle *c = new Circle("circle", "green", 53.3, 1.2, 14.1, 8.5);
    Square *s = new Square("square", "blue", 4.3, 1.0, 17.5, 9.5);
    
    s_g.AddShape(s, 1);
    s_g.AddShape(c, 2);

    sleep (50);

    s_g.Stop();
    comm.StopComm();
    
    sleep (1);

    delete c;
    delete s;

    return 0;
}