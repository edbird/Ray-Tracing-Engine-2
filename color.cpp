#include "color.hpp"







ColorWide operator+(const ColorWide &color, const float x)
{
    ColorWide copy(color);
    copy += x;

    return copy;
}


ColorWide operator*(float scale_factor, const ColorWide& color)
{
    ColorWide copy(color);
    /*copy.ir *= scale_factor;
    copy.r *= scale_factor;
    copy.g *= scale_factor;
    copy.b *= scale_factor;
    copy.uv *= scale_factor;*/
    copy *= scale_factor;

    return copy;
}


ColorWide operator*(const ColorWide &color1, const ColorWide &color2)
{
    ColorWide copy(color2);
    copy.ir *= color1.ir;
    copy.r *= color1.r;
    copy.g *= color1.g;
    copy.b *= color1.b;
    copy.uv *= color1.uv;

    return copy;
}



namespace std
{

    ColorRGB exp(ColorRGB x)
    {
        ColorRGB y(
            std::exp(x.r),
            std::exp(x.g),
            std::exp(x.b));
        
        return y;
    }

    ColorWide exp(ColorWide x)
    {
        ColorWide y(
            std::exp(x.ir),
            std::exp(x.r),
            std::exp(x.g),
            std::exp(x.b),
            std::exp(x.uv));
        
        return y;
    }

}




