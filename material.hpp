#ifndef MATERIAL_HPP
#define MATERIAL_HPP


#include "color.hpp"


enum class MaterialType
{
    DIFFUSE
    // TODO
};
// ROUGH, REFLECTIVE, REFRACTIVE
// DIFFUSE, REFLECTIVE, REFRACTIVE


class Material
{

    public:


    Material()
        : type(MaterialType::DIFFUSE)
        , color(0.0f, 1.0f, 1.0f, 1.0f, 0.0f)
        , fluorescence_red(0.0f)
        , fluorescence_green(0.0f)
        , fluorescence_blue(0.0f)
        , is_thin(false)
    {

    }
    

    Material(const ColorWide &color)
        : type(MaterialType::DIFFUSE)
        , color(color)
        , fluorescence_red(0.0f)
        , fluorescence_green(0.0f)
        , fluorescence_blue(0.0f)
        , is_thin(false)
    {

    }


    ColorWide LightCalculation(const ColorWide &illumination)
    {
        ColorWide color;
        color.r = illumination.r * color.r;
        color.g = illumination.g * color.g;
        color.b = illumination.b * color.b;

        color.r += illumination.uv * fluorescence_red;
        color.g += illumination.uv * fluorescence_green;
        color.b += illumination.uv * fluorescence_blue;

        color.ir = 0.0f;
        color.ir += 0.0f * temperature; // TODO
        color.ir += illumination.ir * color.ir;

        // TODO: do not "create" energy: subtract energy lost to flurescence
        color.uv = illumination.uv * color.uv;

        return color;
    }

    void SetFluorescenceCoefficients(   const float fluorescence_red,
                                        const float fluorescence_green, 
                                        const float fluorescence_blue)
    {
        this->fluorescence_red = fluorescence_red;
        this->fluorescence_green = fluorescence_green;
        this->fluorescence_blue = fluorescence_blue;
    }
    

    void SetThin(bool is_thin, float attenuation_factor)
    {
        this->is_thin = is_thin;
        this->thin_attenuation_factor = attenuation_factor;
    }



    public:

    MaterialType type;

    ColorWide color;
    float fluorescence_red;
    float fluorescence_green;
    float fluorescence_blue;
    float temperature; // TODO

    bool is_thin;
    float thin_attenuation_factor;

};



#endif // MATERIAL_HPP