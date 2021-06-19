#include "screen.hpp"


#include "math_functions.hpp"



Screen::Screen(unsigned int num_pixels_x, unsigned int num_pixels_y)
    : num_pixels_x(num_pixels_x)
    , num_pixels_y(num_pixels_y)
    , aspect_ratio((float)num_pixels_y / (float)num_pixels_x)
{
    std::size_t n = (std::size_t)num_pixels_x * (std::size_t)num_pixels_y;
    pixels.resize(n, ColorWide(0.0f));
}


void Screen::SetPixelResolution(
    const unsigned int num_pixels_x,
    const unsigned int num_pixels_y)
{
    this->num_pixels_x = num_pixels_x;
    this->num_pixels_y = num_pixels_y;
    pixels.clear();

    std::size_t n = (std::size_t)num_pixels_x * (std::size_t)num_pixels_y;
    pixels.resize(n, ColorWide(0.0f));
}

void Screen::GetNumPixels(unsigned int &x, unsigned int &y) const
{
    x = num_pixels_x;
    y = num_pixels_y;
}

float Screen::GetAspectRatio() const
{
    return aspect_ratio;
}

void Screen::ClearToZero()
{
    for(std::size_t j = 0; j < num_pixels_y; ++ j)
    {
        for(std::size_t i = 0; i < num_pixels_x; ++ i)
        {
            std::size_t ix = num_pixels_x * j + i;

            pixels[ix].r = 0.0f;
            pixels[ix].g = 0.0f;
            pixels[ix].b = 0.0f;
        }
    }
}

std::vector<ColorRGB> Screen::GetPixelsRGB() const
{
    std::size_t n = (std::size_t)num_pixels_x * (std::size_t)num_pixels_y;
    std::vector<ColorRGB> tmp(n);

    for(std::size_t j = 0; j < num_pixels_y; ++ j)
    {
        for(std::size_t i = 0; i < num_pixels_x; ++ i)
        {
            std::size_t ix = (std::size_t)num_pixels_x * j + i;

            float r = pixels[ix].r;
            float g = pixels[ix].g;
            float b = pixels[ix].b;

            tmp[ix].r = r;
            tmp[ix].g = g;
            tmp[ix].b = b;
        }
    }

    return tmp;
}

std::vector<ColorRGB> Screen::GetPixelsRGBThermalVision() const
{
    std::size_t n = (std::size_t)num_pixels_x * (std::size_t)num_pixels_y;
    std::vector<ColorRGB> tmp(n);

    for(std::size_t j = 0; j < num_pixels_y; ++ j)
    {
        for(std::size_t i = 0; i < num_pixels_x; ++ i)
        {
            std::size_t ix = (std::size_t)num_pixels_x * j + i;

            float ir = pixels[ix].ir;

            tmp[ix].r = ir;
            tmp[ix].g = ir;
            tmp[ix].b = ir;
        }
    }

    return tmp;
}

void Screen::SetPixel(std::size_t x, std::size_t y, const ColorWide &color)
{
    std::size_t ix = (std::size_t)num_pixels_x * y + x;
    if(ix < pixels.size())
    {
        pixels[ix] = color;
    }
    else
    {
        std::cerr << "Warning: " << __func__ << " ignoring out of bounds pixel" << std::endl;
    }
}

Screen::operator Bitmap() const
{
    Bitmap bitmap(num_pixels_x, num_pixels_y);

    std::size_t nn = (std::size_t)3 * (std::size_t)num_pixels_x * (std::size_t)num_pixels_y;

    std::vector<unsigned char> pixel_format_rgb(nn, 0);

    std::vector<ColorRGB> pixel_tmp = this->GetPixelsRGB();

    for(std::size_t ix = 0; ix < pixel_tmp.size(); ++ ix)
    {
        float r = 255.0f * pixel_tmp[ix].r;
        float g = 255.0f * pixel_tmp[ix].g;
        float b = 255.0f * pixel_tmp[ix].b;

        int (*fclamp_func)(float, int, int) = &fclamp_to_int;

        int rint = (*fclamp_func)(r, 0, 255);
        int gint = (*fclamp_func)(g, 0, 255);
        int bint = (*fclamp_func)(b, 0, 255);

        pixel_format_rgb[3 * ix + 0] = bint;
        pixel_format_rgb[3 * ix + 1] = gint;
        pixel_format_rgb[3 * ix + 2] = rint;
    }

    bitmap.SetPixels(pixel_format_rgb);

    return bitmap;
}