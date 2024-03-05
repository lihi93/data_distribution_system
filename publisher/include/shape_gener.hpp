#ifndef PUBLISHER
#define PUBLISHER

#include <sys/types.h> //recv
#include <sys/socket.h> //recv
#include <netinet/in.h> // sockaddr_in
#include <cstring> // memset
#include <unistd.h> //close
#include <string> 
#include <vector>
#include <atomic>

#include "shape.hpp"
#include "dispatcher.hpp"

using std::string;

class ShapeGenerator
{
public:
    ShapeGenerator(Dispatcher &disp);
    ~ShapeGenerator();
    void AddShape(Ishape *shape, int freq);
    void Stop();

private:
    void GenerateNotifications(Ishape *shape, int freq);
    std::vector<std::pair<Ishape*, int>> shapes_to_freq; 
    Dispatcher &m_disp;
    std::vector<std::thread> m_threads;
    std::atomic_bool is_running;
};

#endif //PUBLISHER