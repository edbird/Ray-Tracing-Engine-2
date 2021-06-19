#ifndef LIGHT_HPP
#define LIGHT_HPP


#include "color.hpp"


enum class LightType
{
    OMNIDIRECTIONAL_POINT_SOURCE
};


class Light
{

    
    public:


    Light(ColorWide emission)
        : emission(emission)
        , type(LightType::OMNIDIRECTIONAL_POINT_SOURCE)
        , intensity{1.0f}
    {

    }

    // get spectral intensity at a point p, the direction of the light
    // is returned in dir
    ColorWide GetIntensity(const geom::vec3f p, geom::vec3f &dir)
    {

        if(type == LightType::OMNIDIRECTIONAL_POINT_SOURCE)
        {
            dir = p - position;

            float distance_square = dir.length_square();

            float intensity = this->intensity;
            intensity /= distance_square;

            ColorWide emission_copy = intensity * emission;

            return emission_copy;
        }

        return ColorWide(0);

    }

    void SetPosition(geom::vec3f position)
    {
        this->position = position;
    }

    void SetDirection(geom::vec3f direction)
    {
        this->direction = direction;
    }

    virtual
    ~Light()
    {

    }



    public:



    ColorWide emission;
    geom::vec3f position; // not always used, depends on the type
    geom::vec3f direction; // not always used, depends on the type
    LightType type;
    float intensity; // physics unit TODO



};


#endif // LIGHT_HPP