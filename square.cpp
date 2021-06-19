#include "square.hpp"


#include "ray.hpp"
#include "geom.hpp"
#include "hit.hpp"
#include "material.hpp"


Hit Square::Intersect(const Ray& ray)
{


    Hit hit;

    Material material_copy = material;


    geom::vec3f vec_to_p1 = p1 - ray.start;
    geom::vec3f ray_dir = ray.dir;
    float num = dot(vec_to_p1, n1);
    float denom = dot(ray_dir, n1);
    float t = num / denom;
    //if(t <= 0.0f) return hit;

    // interior test
    geom::vec3f p = ray.start + ray.dir * t;
    float k1 = dot(cross(p2 - p1, p - p1), n1);
    float k2 = dot(cross(p3 - p2, p - p2), n1);
    float k3 = dot(cross(p1 - p3, p - p3), n1);

    bool valid = false;

    if((k1 >= 0) && (k2 >= 0) && (k3 >= 0))
    {
        // valid
        // incident ray is the same side as the normal vector
        // direction of normal does not change this test

        if(t > 0.0f) valid = true;
    }
    else if((k1 <= 0) && (k2 <= 0) && (k3 <= 0))
    {
        // invalid
        // impossible
        std::cerr << "Warning: " << "point with k1<=0, k2<=0, k3<=0" << std::endl;
        //return hit;

        std::cout << "first" << std::endl;
        std::cin.get();
    }
    else
    {
        //return hit;
    }


    if(valid)
    {
        if(this->checker_pattern_enable)
            apply_checker(p, material_copy);

        hit.distance = t;
        hit.position = p;
        hit.normal = n1;
        hit.material = material_copy;
        hit.valid = true;

        return hit;
    }

    //std::cout << "Square::" << __func__ << " first test was not valid, second..." << std::endl;

    vec_to_p1 = p4 - ray.start;
    num = dot(vec_to_p1, n2);
    denom = dot(ray_dir, n2);
    t = num / denom;

    //std::cout << "t=" << t << std::endl;

    // interior test
    p = ray.start + ray.dir * t;
    k1 = dot(cross(p3 - p4, p - p4), n2);
    k2 = dot(cross(p2 - p3, p - p3), n2);
    k3 = dot(cross(p4 - p2, p - p2), n2);


    if((k1 >= 0) && (k2 >= 0) && (k3 >= 0))
    {
        // valid
        // incident ray is the same side as the normal vector
        // direction of normal does not change this test
        //std::cout << "valid internal" << std::endl;

        if(t > 0.0f) valid = true;
    }
    else if((k1 <= 0) && (k2 <= 0) && (k3 <= 0))
    {
        // invalid
        // impossible
        std::cerr << "Warning: " << "point with k1<=0, k2<=0, k3<=0" << std::endl;
        std::cout << "second" << std::endl;

        std::cout << "t=" << t << std::endl;
        std::cout << k1 << ", " << k2 << ", " << k3 << std::endl;

        std::cin.get();
        //return hit;
    }
    else
    {
        //return hit;
    }

    // TODO: THIS WILL NOT WORK IF THE SECOND t is < the FIRST t

    if(valid)
    {
        if(this->checker_pattern_enable)
            apply_checker(p, material_copy);

        hit.distance = t;
        hit.position = p;
        hit.normal = n2;
        hit.material = material_copy;
        hit.valid = true;

        return hit;
    }
    //std::cout << "not valid" << std::endl;
    //std::cin.get();

    return hit;
}


void Square::SetCheckerPattern(bool enable)
{
    this->checker_pattern_enable = enable;
}