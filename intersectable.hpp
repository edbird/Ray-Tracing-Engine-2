#ifndef INTERSECTABLE_HPP
#define INTERSECTABLE_HPP






#include "color.hpp"


#include "hit.hpp"




// material applies to 2 dimensional surface which ray intersects
#include "material.hpp"
// medium applies to 3 dimensional volume which ray travels through
#include "medium.hpp"

#include "ray.hpp"
#include "hit.hpp"



class Intersectable
{

    protected:

    // material? color?
    Material material;

    public:

    Intersectable(const Material &material)
        : material(material)
    {

    }
    
    virtual
    Hit Intersect(const Ray& ray) = 0;

    


/*
    virtual
    Hit Intersect()
    {
        Hit hit;
        return hit;
    }

    virtual
    bool IntersectTest() const
    {
        return false;
    }
*/
};









#endif // INTERSECTABLE_HPP