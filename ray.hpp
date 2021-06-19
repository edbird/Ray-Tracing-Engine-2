#ifndef RAY_HPP
#define RAY_HPP



#include "geom.hpp"
#include "color.hpp"


#include <iostream>



class Ray
{

    friend std::ostream& operator<<(std::ostream& os, const Ray &ray);

    public:

    Ray()
        : distance(0.0f)
        , n(1.0f)
        , medium_transmission_color_factor(1.0f, 1.0f, 1.0f, 1.0f, 1.0f)
        , intersection_color_factor(1.0f, 1.0f, 1.0f, 1.0f, 1.0f)
        , source_light_PSD(0.0f, 0.0f, 0.0f, 0.0f, 0.0)
    {

    }

/*
    Ray(geom::vec3f start, geom::vec3f direction)
        : start(start)
        , dir(direction)
        , medium_transmission_color_factor(1.0f, 1.0f, 1.0f, 1.0f, 1.0f)
        , intersection_color_factor(1.0f, 1.0f, 1.0f, 1.0f, 1.0f)
        , source_light_PSD(0.0f, 0.0f, 0.0f, 0.0f, 0.0)
        , n(1.0f)
    {

    }
*/

    Ray(geom::vec3f start, geom::vec3f end)
        : start(start)
        , end(end)
        , n(1.0f)
    {
        geom::vec3f diff = end - start;
        distance = diff.length();
        diff.normalize();
        dir = diff;
    }
    

    void SetStart(geom::vec3f start)
    {
        this->start = start;
    }

    void SetEnd(geom::vec3f end)
    {
        this->end = end;
    }

    void SetDirection(geom::vec3f dir)
    {
        this->dir = dir.unit();
    }

    void SetRefractiveIndex(float n)
    {
        this->n = n;
    }



    public:

    geom::vec3f start;
    geom::vec3f end;
    geom::vec3f dir;
    float distance;     // TODO: does it make sense to store this? ray should have an END if it has a fixed distance
    float n;            // refractive index in current material, at position start

    // when the ray passes through a medium, the color factor is calculated
    // it is calculated taking into account the distance travelled
    ColorWide medium_transmission_color_factor;
    // when the ray intersects an object, the color factor is calculated
    ColorWide intersection_color_factor;
    // source light PSD
    // TODO: make this a different object to ColorWide?
    ColorWide source_light_PSD;


};






#endif // RAY_HPP