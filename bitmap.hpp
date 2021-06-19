#ifndef BITMAP_HPP
#define BITMAP_HPP


#include <iostream>
#include <fstream>
#include <vector>


// bitmap file header
struct __attribute__((packed)) bitmap_header
{

    char BM[2];
    unsigned int FSIZE;
    char RES0[2];
    char RES1[2];
    unsigned int DATA_OFFSET;

};


// bitmap information header
struct __attribute__((packed)) bitmap_dip_header
{

    unsigned int DIP_HEADER_SIZE;
    int WIDTH;
    int HEIGHT;
    unsigned short PLANES;
    unsigned short BITS_PER_PIXEL;
    unsigned int COMPRESSION_METHOD;
    unsigned int IMAGE_SIZE;
    int HRES;
    int VRES;
    unsigned int NCOLORPALETTE;
    unsigned int NCOLORIMPORTANT;

};


class Bitmap
{

    int get_width_bytes_disk(unsigned short bits_per_pixel, int width)
    {
        int width_bytes_disk = 4 * ((bits_per_pixel * width + 31) / 32);
        return width_bytes_disk;
    }

    int get_width_bytes_mem(unsigned short bits_per_pixel, int width)
    {
        int width_bytes_mem = (bits_per_pixel / 8) * width;
        return width_bytes_mem;
    }

    unsigned int get_image_bytes_disk(
        unsigned short bits_per_pixel,
        int width,
        int height)
    {
        int width_bytes_disk = get_width_bytes_disk(bits_per_pixel, width);
        //unsigned int image_bytes_disk = (bits_per_pixel / 8) * width_bytes_disk * height;
        unsigned int image_bytes_disk = width_bytes_disk * height;

        return image_bytes_disk;
    }

    unsigned int get_image_bytes_mem(
        unsigned short bits_per_pixel,
        int width,
        int height)
    {
        return (bits_per_pixel / 8) * width * height;
    }

    public:


    std::vector<unsigned char> bmp_data;
    int width;
    int height;
    unsigned short bits_per_pixel; // bits per pixel

    int hres;
    int vres;


    Bitmap()
        : width(0)
        , height(0)
        , bits_per_pixel(24) // bits per pixel
        , hres(0)
        , vres(0)
    {
    }


    Bitmap(int width, int height)
        : width(width)
        , height(height)
        , bits_per_pixel(24) // bits per pixel
    {

        //int width_bytes_disk = get_width_bytes_disk(bits_per_pixel, width);
        //std::cout << "width=" << width << " width_bytes_disk=" << width_bytes_disk << std::endl;

        unsigned int bmp_bytes_mem = get_image_bytes_mem(bits_per_pixel, width, height);
        bmp_data.resize(bmp_bytes_mem, 0);

    }


    void SetPixels(const std::vector<unsigned char> &pixels)
    {
        if(pixels.size() != bmp_data.size())
        {
            std::cerr << "Warning " << __func__ << " length of pixels vector differs to internal pixel data" << std::endl;
        }

        std::size_t m = std::min(pixels.size(), bmp_data.size());
        for(std::size_t ix = 0; ix < m; ++ ix)
        {
            bmp_data[ix] = pixels[ix];
        }
    }


    void SetPixel(int x, int y,
        unsigned char r, unsigned char g, unsigned char b)
    {
        bmp_data.at((bits_per_pixel / 8) * (y * width + x) + 0) = b; // TODO or b?
        bmp_data.at((bits_per_pixel / 8) * (y * width + x) + 1) = g; // TODO or b?
        bmp_data.at((bits_per_pixel / 8) * (y * width + x) + 2) = r; // TODO or b?
            // TODO: what is the order for alpha
    }


    void GetPixel(const int x, const int y,
        unsigned char &r, unsigned char &g, unsigned char &b) const
    {
        b = bmp_data.at((bits_per_pixel / 8) * (y * width + x) + 0); // TODO or b?
        g = bmp_data.at((bits_per_pixel / 8) * (y * width + x) + 1); // TODO or b?
        r = bmp_data.at((bits_per_pixel / 8) * (y * width + x) + 2); // TODO or b?
    }


    void Write(const std::string &filename)
    {
        std::ofstream ofile(filename, std::ios::binary);
        if(!ofile.is_open())
        {
            throw "error: cannot open file";
        }
        else
        {

            int width_bytes_disk = get_width_bytes_disk(bits_per_pixel, width);
            int width_bytes_mem = get_width_bytes_mem(bits_per_pixel, width);
            //std::cout << "width_bytes_mem=" << width_bytes_mem << " "
            //          << "width_bytes_disk=" << width_bytes_disk << std::endl;
            unsigned int image_bytes_disk = get_image_bytes_disk(bits_per_pixel, width, height);
            unsigned int image_bytes_mem = get_image_bytes_mem(bits_per_pixel, width, height);

            // write bitmap header
            bitmap_header header;
            header.BM[0] = 'B';
            header.BM[1] = 'M';

            // set dip header values
            bitmap_dip_header dip_header;
            dip_header.DIP_HEADER_SIZE = sizeof(bitmap_dip_header);
            dip_header.WIDTH = width;
            dip_header.HEIGHT = height;
            dip_header.PLANES = 1;
            dip_header.BITS_PER_PIXEL = bits_per_pixel;
            dip_header.COMPRESSION_METHOD = 0;
            dip_header.IMAGE_SIZE = image_bytes_disk;
            dip_header.HRES = hres;
            dip_header.VRES = vres;
            dip_header.NCOLORPALETTE = 0;
            dip_header.NCOLORIMPORTANT = 0;

            /*int bmp_data_size = (dip_header.BITS_PER_PIXEL / 8) *
                                 dip_header.WIDTH *
                                 dip_header.HEIGHT;*/

            // TODO: can remove bmp_data_size, because bmp_data_size == bmp_data_size_pad
            // if width_bytes_disk == width (used bmp_data_size once below)
            /*int bmp_data_size_pad = (dip_header.BITS_PER_PIXEL / 8) *
                                     width_bytes_disk *
                                     dip_header.HEIGHT;*/

            unsigned int fsize = sizeof(bitmap_header) +
                                 sizeof(bitmap_dip_header) + 
                                 image_bytes_disk; //bmp_data_size_pad;

            header.FSIZE = fsize;
            header.RES0[0] = 0;
            header.RES0[1] = 0;
            header.RES1[0] = 0;
            header.RES1[1] = 0;
            header.DATA_OFFSET = sizeof(bitmap_header) + sizeof(bitmap_dip_header);

            // write file
            ofile.write((char*)&header, sizeof(bitmap_header));
            ofile.write((char*)&dip_header, sizeof(bitmap_dip_header));

            if(width_bytes_disk == width_bytes_mem)
            {
                ofile.write((char*)bmp_data.data(), image_bytes_mem);
            }
            else
            {
                const char pad4[] = {0, 0, 0, 0};
                const int n_bytes_pad = width_bytes_disk - width_bytes_mem;
                //std::cout << "n_bytes_pad=" << n_bytes_pad << std::endl;
                for(int y = 0; y < height; ++ y)
                {
                    int offset_mem = y * width_bytes_mem;
                    ofile.write( (char*)(&bmp_data[offset_mem]), width_bytes_mem );
                    ofile.write( &pad4[0], n_bytes_pad );
                }
            }

            ofile.close();
        }
    }


    void Read(const std::string &filename)
    {

        std::ifstream ifile(filename, std::ios::binary);
        if(!ifile.is_open())
        {
            throw "error: cannot open file";
        }
        else
        {

            // read BMP header
            bitmap_header header;
            ifile.read((char*)&header, sizeof(bitmap_header));

            //std::cout << header.BM[0] << header.BM[1] << std::endl;
            //std::cout << header.FSIZE << std::endl;
            //std::cout << header.RES0[0] << header.RES0[1] << std::endl;
            //std::cout << header.RES1[0] << header.RES1[1] << std::endl;
            //std::cout << header.DATA_OFFSET << std::endl;


            // read DIP header
            bitmap_dip_header dip_header;
            ifile.read((char*)&dip_header, sizeof(dip_header));

            std::cout << "BMP Resolution: "
                      << dip_header.WIDTH << " x "
                      << dip_header.HEIGHT << std::endl;


            // TODO: put at end
            width = dip_header.WIDTH;
            height = dip_header.HEIGHT;
            bits_per_pixel = dip_header.BITS_PER_PIXEL;

            hres = dip_header.HRES;
            vres = dip_header.VRES;

            int width_bytes_disk = get_width_bytes_disk(bits_per_pixel, width);
            int width_bytes_mem = get_width_bytes_mem(bits_per_pixel, width);
            //std::cout << "width_bytes_mem=" << width_bytes_mem << " "
            //          << "width_bytes_disk=" << width_bytes_disk << std::endl;
            unsigned int image_bytes_disk = get_image_bytes_disk(bits_per_pixel, width, height);
            unsigned int image_bytes_mem = get_image_bytes_mem(bits_per_pixel, width, height);


            /*
            int bmp_data_size = (dip_header.BITS_PER_PIXEL / 8) *
                                 dip_header.WIDTH *
                                 dip_header.HEIGHT;
            std::cout << "Bitmap Pixel Data size: " << bmp_data_size << std::endl;
            */


            if(image_bytes_disk != dip_header.IMAGE_SIZE)
            {
                std::cerr << "Error: image_bytes_disk=" << image_bytes_disk << " "
                          << "dip_header.IMAGE_SIZE=" << dip_header.IMAGE_SIZE << std::endl;
            }

            // read data
            unsigned int data_offset = header.DATA_OFFSET;

            bmp_data.resize(image_bytes_mem, 0);

            //std::cout << "current gpointer: " << ifile.tellg() << std::endl;
            //std::cout << "seeking to: " << data_offset << std::endl;

            ifile.seekg(data_offset, ifile.beg);

            if(width_bytes_disk == width_bytes_mem)
            {
                ifile.read((char*)&bmp_data[0], image_bytes_mem);
            }
            else
            {
                for(int y = 0; y < height; ++ y)
                {
                    int offset_disk = y * width_bytes_disk;
                    ifile.seekg(data_offset + offset_disk, ifile.beg);

                    int offset_mem = y * width_bytes_mem;
                    ifile.read( (char*)(&bmp_data[offset_mem]), width_bytes_mem );
                }
            }
            ifile.close();

        }

    }



};


#endif // BITMAP_HPP