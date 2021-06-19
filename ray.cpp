#include "ray.hpp"




std::ostream& operator<<(std::ostream& os, const Ray &ray)
{
    os << ray.start << " -> " << ray.end << " (d=" << ray.distance << ")" << std::endl;
    os << ray.dir << std::endl;
    os << "n=" << ray.n << std::endl;

    return os;
}