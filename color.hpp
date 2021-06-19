#ifndef COLOR_HPP
#define COLOR_HPP


#include <cmath>
#include <iostream>



class ColorRGB
{

    public:

    ColorRGB()
        : r(0.0f), g(0.0f), b(0.0f)
    {

    }

    ColorRGB(float r, float g, float b)
        : r(r), g(g), b(b)
    {

    }

    ~ColorRGB()
    {

    }


    public:

    float r;
    float g;
    float b;

};


// TODO: negative multiplier should be clamped to zero


class ColorWide
{

    friend std::ostream& operator<<(std::ostream& os, const ColorWide &color)
    {
        os << "ColorWide: [ " << color.ir << ", "
                              << color.r << ", "
                              << color.g << ", "
                              << color.b << ", "
                              << color.uv << "]";
        
        return os;
    }


    public:

    ColorWide()
        : ir(0.0f), r(0.0f), g(0.0f), b(0.0f), uv(0.0f)
    {

    }


    ColorWide(float ir, float r, float g, float b, float uv)
        : ir(ir), r(r), g(g), b(b), uv(uv)
    {

    }


    // used to produce ColorWide(0)
    ColorWide(float intensity)
        : ir(0.0f)
        , r(intensity)
        , g(intensity)
        , b(intensity)
        , uv(0.0f)
    {

    }

    ~ColorWide()
    {

    }


    ColorWide operator-() const
    {
        ColorWide copy(
            -this->ir,
            -this->r,
            -this->g,
            -this->b,
            -this->uv
        );
        return copy;
    }

    ColorWide operator-=(const ColorWide &color)
    {
        this->operator+=(-color);

        return *this;
    }

    ColorWide operator+=(const ColorWide &color)
    {
        this->ir += color.ir;
        this->r += color.r;
        this->g += color.g;
        this->b += color.b;
        this->uv += color.uv;

        return *this;
    }


    ColorWide operator-=(const float x)
    {
        this->operator+=(-x);

        return *this;
    }

    ColorWide operator+=(const float x)
    {
        this->ir += x;
        this->r += x;
        this->g += x;
        this->b += x;
        this->uv += x;

        return *this;
    }


    ColorWide operator*=(const ColorWide &color)
    {
        this->ir *= color.ir;
        this->r *= color.r;
        this->g *= color.g;
        this->b *= color.b;
        this->uv *= color.uv;

        return *this;
    }

    ColorWide operator*=(const float x)
    {
        this->ir *= x;
        this->r *= x;
        this->g *= x;
        this->b *= x;
        this->uv *= x;

        return *this;
    }


    public:

    float ir;
    float r;
    float g;
    float b;
    float uv;



};


/*
ColorWide operator-(const ColorWide &color)
{
    ColorWide copy;
    copy -= color;
    return copy;
}
*/


ColorWide operator+(const ColorWide &color, const float x);

ColorWide operator*(float scale_factor, const ColorWide& color);

ColorWide operator*(const ColorWide &color1, const ColorWide &color2);



namespace std
{

    ColorRGB exp(ColorRGB x);

    ColorWide exp(ColorWide x);

}


/*
class ColorBase
{


    public:

    ColorBase()
    {

    }

    virtual
    ~ColorBase()
    {

    }

};


class ColorMonochrome
{

    public:

    ColorMonochrome()
    {

    }

    virtual
    ~ColorMonochrome()
    {

    }

    private:

    float g; // grey component


};





class ColorRGB
{

    public:

    ColorRGB()
    {

    }

    virtual
    ~ColorRGB()
    {

    }


    private:

    float r;
    float g;
    float b;

};


class ColorIRRGBUV // think of a better name
{

    public:

    ColorIRRGBUV()
    {

    }

    virtual
    ~ColorIRRGBUV()
    {

    }


    private:

    float ir;
    float r;
    float g;
    float b;
    float uv;

};
*/


#endif