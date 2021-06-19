#ifndef SCREEN_HPP
#define SCREEN_HPP


#include "bitmap.hpp"

#include "color.hpp"


// TODO: implement this as part of Camera
class Screen
{

    public:

    Screen(unsigned int num_pixels_x, unsigned int num_pixels_y);


    void SetPixelResolution(
        const unsigned int num_pixels_x,
        const unsigned int num_pixels_y);

    void GetNumPixels(unsigned int &x, unsigned int &y) const;

    float GetAspectRatio() const;

    void ClearToZero();

    std::vector<ColorRGB> GetPixelsRGB() const;

    std::vector<ColorRGB> GetPixelsRGBThermalVision() const;

    void SetPixel(std::size_t x, std::size_t y, const ColorWide &color);

    operator Bitmap() const;

    private:
    
    unsigned int num_pixels_x;
    unsigned int num_pixels_y;
    float aspect_ratio;

    std::vector<ColorWide> pixels;


};






#endif // SCREEN_HPP