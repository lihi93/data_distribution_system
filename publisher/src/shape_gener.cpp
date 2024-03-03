#include <thread>
#include <iostream>

#include "shape_gener.hpp"


ShapeGenerator::ShapeGenerator(Dispatcher *disp):
    m_disp(disp) {}


ShapeGenerator::~ShapeGenerator()
{
    for (auto &it : m_threads)
    {
        it.join();
    }
}
void ShapeGenerator::AddShape(Ishape *shape, int freq)
{
    m_threads.emplace_back(&ShapeGenerator::GenerateShapes, this, m_disp, shape, freq);
}

void ShapeGenerator::GenerateShapes(Dispatcher *disp, Ishape *shape, int freq)
{
    string serialized_shape = Serialize(shape);

    while(true)
    {
        sleep(freq);
        disp->Notify(shape->GetName(), serialized_shape);
    }
}

string ShapeGenerator::Serialize(Ishape *shape)
{
    string shape_string("/1=" + shape->GetName() + "/2=" +  shape->GetColor() + "/3=" + std::to_string(shape->GetSize()) + "/4=" + std::to_string(shape->GetLatitude()) + "/5=" + std::to_string(shape->GetLongitude()) + "/6=" + std::to_string(shape->GetAltitude()));
    return shape_string;
}