#ifndef SPHERE_HPP
#define SPHERE_HPP


#include "intersectable.hpp"



#include "precision_epsilon.hpp"


class Sphere : public Intersectable
{

	public:

	geom::vec3f center;
	float radius;


	Sphere(const geom::vec3f center, float radius, const Material &material)
		: Intersectable(material)
    {
		this->center = center;
		this->radius = radius;
	}


	Hit Intersect(const Ray& ray)
    {
		Hit hit;
		geom::vec3f vec_from_center = ray.start - center;
		float a = dot(ray.dir, ray.dir);
		float b = dot(vec_from_center, ray.dir) * 2.0f;
		float c = dot(vec_from_center, vec_from_center) - radius * radius;
		float discr = b * b - 4.0f * a * c;
		if (discr < 0) return hit;
		float sqrt_discr = sqrtf(discr);
		float t1 = (-b + sqrt_discr) / 2.0f / a;	// t1 >= t2 for sure
		float t2 = (-b - sqrt_discr) / 2.0f / a;
		if (t1 <= 0) return hit; // TODO: not sure about logic at/from this point

        if(t2 >= 0.0f && t2 >= precision_elipson)
        {
            hit.distance = t2;
            hit.valid = true;
        }
        else if(t1 >= precision_elipson)
        {
            hit.distance = t1;
            hit.valid = true;
        }

		//hit.distance = (t2 > 0) ? t2 : t1;
		hit.position = ray.start + ray.dir * hit.distance;
		hit.normal = (hit.position - center) * (1.0f / radius);
		hit.material = material;
        //hit.valid = true;
		return hit;
	}
};



#endif // SPHERE_HPP