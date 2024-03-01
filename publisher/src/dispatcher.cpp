#include "dispatcher.hpp"

void Dispatcher::Register(string shape, std::shared_ptr<Isub> sub)
{
    shape_to_subs[shape].push_front(sub);
}

void Dispatcher::Notify(string shape, string msg)
{
    auto it = shape_to_subs[shape].begin();
    while (it != shape_to_subs[shape].end())
    {
        if (-1 == (*it)->Notify(msg))
        {
            it = shape_to_subs[shape].erase(it);
        }
        else
        {
            ++it; 
        }
    }
}
