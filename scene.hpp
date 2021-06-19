#ifndef SCENE_HPP
#define SCENE_HPP




#include "bitmap.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include "intersectable.hpp"
#include "light.hpp"
#include "camera_simple.hpp"


#include <vector>

#include <map>


class Scene
{



    public:


    Scene()
    {

    }


    void Build();

    void getFirstIntersect(Hit &nearest_hit, const Ray& ray);

    void Render(Bitmap &bitmap);

    void RegisterTexture(const std::string texture_string, Bitmap &bitmap)
    {
        texture_map[texture_string] = bitmap;
    }


    // used in while loop to emulate recursion without heavy stack use
    // return true to continue recursing, return false to quit
    // 
    // not sure how to handle forking due to refraction in this case?
    /*
    ColorWide Trace() const
    {

        std::vector<Intersectable*>::const_iterator it{objects.cbegin()};
        for(; it != objects.cend(); ++ it)
        {
            if(it->IntersectionTest(ray))
        }

    }
    */
    // should Trace be a member of Ray?
    // should IntersectionTest be a member of Ray, Object or a non-member function?
    // or member of the Scene class



    // hetrogenious collection of materials
    // not used

    // hetrogenious intersectable object collection
    std::vector<Intersectable*> objects;

    // hetrogenious light collection
    std::vector<Light*> lights;

    // single camera
    CameraSimple camera;

    // texture maps
    std::map<std::string, Bitmap> texture_map;


};



#endif // SCENE_HPP