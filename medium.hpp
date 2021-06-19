#ifndef MEDIUM_HPP
#define MEDIUM_HPP


#include "color.hpp"



class Medium
{

    public:

    Medium()
        : transmission_coeff(1.0f, 1.0f, 1.0f, 1.0f, 1.0f)
    {

    }


    ColorWide LightCalculation( const ColorWide &illumination,
                                const float distance)
    {
        ColorWide transmission_coeff_inv = -transmission_coeff + 1.0f;
        ColorWide factor = std::exp(-distance * transmission_coeff_inv);

        return illumination * factor;
    }

    private:

    ColorWide transmission_coeff;

};



#endif // MEDIUM_HPP