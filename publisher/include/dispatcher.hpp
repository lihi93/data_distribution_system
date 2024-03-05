#ifndef DISPATCHER
#define DISPATCHER

#include <string>
#include <unordered_map>
#include <list>
#include <memory> //shared_ptr

#include "isub.hpp"
#include "dispatcher.hpp"

using std::string;
using std::unordered_map;
using std::list;

class Dispatcher
{
public:
    Dispatcher() = default;
    ~Dispatcher() = default;

    void Register(string shape, std::shared_ptr<Isub> sub);
    void Notify(string shape, string shape_data);
private:
    unordered_map<string, list<std::shared_ptr<Isub>>> shape_to_subs;
};



#endif //DISPATCHER