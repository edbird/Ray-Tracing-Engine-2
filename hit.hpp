#ifndef HIT_HPP
#define HIT_HPP


#include "material.hpp"
#include "geom.hpp"


// Hit is a bit like a ray with some of the same variables, some additional ones
// and some missing ones
class Hit
{

    public:


    Hit()
        : valid(false)
        , distance(0.0f)
    {
    }



    bool valid;
    float distance;
    geom::vec3f position;
    geom::vec3f normal;
        // the distance along the currently traced ray where the hit
        // occurs

    Material material;
        // copy of the data associated with the material of the object
        // which is hit


};


#endif // HIT_HPP