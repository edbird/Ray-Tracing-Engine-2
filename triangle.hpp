#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP



#include "intersectable.hpp"


class Triangle : public Intersectable
{

    public:

    // TODO: store points
    geom::vec3f p1;
    geom::vec3f p2;
    geom::vec3f p3;

    geom::vec3f v1;
    geom::vec3f v2;
    geom::vec3f normal;


    // infinite plane specified by 3 arbitrary points
    Triangle(   const geom::vec3f p1,
                const geom::vec3f p2,
                const geom::vec3f p3,
                const Material &material)
                /*
    Triangle(   const geom::vec3f p1,
                const geom::vec3f p2,
                const geom::vec3f p3,
                Material* _material)
        : Intersectable(_material)
        */
        : Intersectable(material)
    {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
        v1 = p2 - p1;
        v2 = p3 - p1;
        //normal = normalize(cross(v1, v2));
        normal = cross(v1, v2);
        normal.normalize();
    }


    Hit Intersect(const Ray& ray)
    {


        Hit hit;
        geom::vec3f vec_to_p1 = p1 - ray.start;
        geom::vec3f ray_dir = ray.dir;
        float num = dot(vec_to_p1, normal);
        float denom = dot(ray_dir, normal);
        float t = num / denom;
        if(t <= 0.0f) return hit;

        // interior test
        geom::vec3f p = ray.start + ray.dir * t;
        float k1 = dot(cross(p2 - p1, p - p1), normal);
        float k2 = dot(cross(p3 - p2, p - p2), normal);
        float k3 = dot(cross(p1 - p3, p - p3), normal);
        if((k1 >= 0) && (k2 >= 0) && (k3 >= 0))
        {
            // valid
            // point inside
        }
        else if((k1 <= 0) && (k2 <= 0) && (k3 <= 0))
        {
            // invalid
            // impossible
            std::cerr << "Warning: " << "point with k1<=0, k2<=0, k3<=0" << std::endl;
            return hit;
        }
        else
        {
            return hit;
        }


        hit.distance = t;
        hit.position = p;
        hit.normal = normal;
        hit.material = material;
        hit.valid = true;

    /*
        std::cout << __func__ << std::endl;
        std::cout << ray << std::endl;
        std::cout << p1 << " " << p2 << " " << p3 << std::endl;
        std::cout << hit.position << std::endl;
        std::cout << hit.distance << std::endl;
        std::cout << hit.normal << std::endl;
        std::cout << "---" << std::endl;
        std::cout << "vec_to_p1=" << vec_to_p1 << std::endl;
        std::cout << "ray_dir=" << ray_dir << std::endl;
    */

        return hit;
    }


};



#endif // TRIANGLE_HPP