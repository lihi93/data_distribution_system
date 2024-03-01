#include "shape.hpp"

Ishape::Ishape(){}

Ishape::Ishape(std::string name, std::string color, float size, float lat, float lon, float alt){}
Ishape::~Ishape(){}

/******************************** Circle ***************************************/

Circle::Circle(std::string name, std::string color, float size, 
float lat, float lon, float alt)
    :name(name), color(color), size(size), latitude(lat), 
        longitude(lon), altitude(alt) {}


std::string Circle::GetName() const {
    return name;
}

std::string Circle::GetColor() const {
    return color;
}

float Circle::GetSize() const {
    return size;
}

float Circle::GetLatitude() const {
    return latitude;
}

float Circle::GetLongitude() const {
    return longitude;
}

float Circle::GetAltitude() const {
    return altitude;
}

/******************************** Square ***************************************/

Square::Square(std::string name, std::string color, float size, 
float lat, float lon, float alt)
    : name(name), color(color), size(size), latitude(lat), 
        longitude(lon), altitude(alt) {}

std::string Square::GetName() const
{
    return name;
}

std::string Square::GetColor() const
{
    return color;
}

float Square::GetSize() const
{
    return size;
}

float Square::GetLatitude() const
{
    return latitude;
}

float Square::GetLongitude() const
{
    return longitude;
}

float Square::GetAltitude() const
{
    return altitude;
}

/**************************************************************************/

shape_data_t StringToStruct(std::string shape_string)
{
    shape_data_t to_ret;
   
    auto it = shape_string.begin();
    while (it < shape_string.end())
    {
        if (*it == '/')
        {
            ++it;
            if (*it == '1')
            {
                it += 2;
                while (it < shape_string.end() && *it != '/')
                {
                    to_ret.name.push_back(*it);
                    ++it;
                }
            }
            else if (*it == '2')
            {
                it += 2;
                while (it < shape_string.end() && *it != '/')
                {
                    to_ret.color.push_back(*it);
                    ++it;
                }
            }
            else if (*it == '3')
            {
                std::string temp;
                it += 2;
                while (it < shape_string.end() && *it != '/')
                {
                    temp.push_back(*it);
                    ++it;
                }
                to_ret.size = std::stod(temp);
            }
            else if (*it == '4')
            {
                std::string temp;
                it += 2;
                while (it < shape_string.end() && *it != '/')
                {
                    temp.push_back(*it);
                    ++it;
                }
                to_ret.lat = std::stod(temp);
            }
            else if (*it == '5')
            {
                std::string temp;
                it += 2;
                while (it < shape_string.end() && *it != '/')
                {
                    temp.push_back(*it);
                    ++it;
                }
                to_ret.lon = std::stod(temp);
            }
            else if (*it == '6')
            {
                std::string temp;
                it += 2;
                while (it < shape_string.end() && *it != '/')
                {
                    temp.push_back(*it);
                    ++it;
                }
                to_ret.alt = std::stod(temp);
            }
        }
        else
        {
            ++it;
        }
    }
    return to_ret;
}
