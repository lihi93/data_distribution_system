#ifndef SHAPE
#define SHAPE

#include <string> 

enum SHAPES {SQUARE, CIRCLE, RECTANGLE};

typedef struct ShapeData
{
public:
    std::string name;
    std::string color;
    float size;
    float lat;
    float lon;
    float alt;
}shape_data_t;

class Ishape {
public:
    Ishape();
    Ishape(std::string name, std::string color, float size, float lat, float lon, float alt);
    virtual ~Ishape();

    virtual std::string GetName() const = 0;
    virtual std::string GetColor() const = 0;
    virtual float GetSize() const = 0;
    virtual float GetLatitude() const = 0;
    virtual float GetLongitude() const = 0;
    virtual float GetAltitude() const = 0;
};

class Circle : public Ishape 
{
public:
    Circle(std::string name, std::string color, float size, float lat, float lon, float alt);
    ~Circle() = default;

    std::string GetName() const;
    std::string GetColor() const;
    float GetSize() const;
    float GetLatitude() const;
    float GetLongitude() const;
    float GetAltitude() const;
private:
    std::string name;
    std::string color;
    float size;
    float latitude;
    float longitude;
    float altitude;
};

class Square : public Ishape 
{
public:
    Square(std::string name, std::string color, float size, float lat, float lon, float alt);
    ~Square() = default;

    std::string GetName() const;
    std::string GetColor() const;
    float GetSize() const;
    float GetLatitude() const;
    float GetLongitude() const;
    float GetAltitude() const;
private:
    std::string name;
    std::string color;
    float size;
    float latitude;
    float longitude;
    float altitude;
};

shape_data_t StringToStruct(std::string shape_string);
std::string ShapeToString(Ishape *shape);

#endif
