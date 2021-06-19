#include "math_functions.hpp"


#include <cmath>


float deg_to_rad(float deg)
{
    // atan(1) = 45 degrees / 1/4 pi rad
    const float pi = 4.0f * std::atan(1.0f);

    return pi * (deg / 180.0f);
}

float rad_to_deg(float rad)
{
    // atan(1) = 45 degrees / 1/4 pi rad
    const float pi = 4.0f * std::atan(1.0f);

    return 180.0f * (rad / pi);
}

int fsign(float x)
{
    if(x < 0.0f)
    {
        return -1;
    }
    else if(x > 0.0f)
    {
        return 1;
    }
    
    return 0;
}

int fclamp_to_int(float x, int min, int max)
{
    float fmin = (float)min;
    float fmax = (float)max;
    if(x <= fmin) return min;
    if(x >= fmax) return max;
    return (int)(x + 0.5f);
}


int fclamp_log_to_int(float x, int min, int max)
{
    // fscale = 255.0f / log(255.0f)
    const float fscale = 46.018385143006135;
    float xx = fscale * std::log(x + 1.0f);

    return fclamp_to_int(xx, min, max);
}