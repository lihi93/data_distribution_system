#include <thread>
#include <atomic>
#include <iostream>

#include "shape_gener.hpp"


ShapeGenerator::ShapeGenerator(Dispatcher &disp):
    m_disp(disp), is_running(true) {}


ShapeGenerator::~ShapeGenerator()
{
    for (auto &it : m_threads)
    {
        it.join();
    }
}
void ShapeGenerator::AddShape(Ishape *shape, int freq)
{
    m_threads.emplace_back(&ShapeGenerator::GenerateNotifications, this, shape, freq);
}

void ShapeGenerator::Stop()
{
    is_running.store(false, std::memory_order_relaxed);
}

void ShapeGenerator::GenerateNotifications(Ishape *shape, int freq)
{
    string serialized_shape = ShapeToString(shape);

    while(is_running.load(std::memory_order_relaxed))
    {
        int time_left_to_sleep = freq;
        while(time_left_to_sleep = sleep(time_left_to_sleep))
        {};
        m_disp.Notify(shape->GetName(), serialized_shape);
    }
}
