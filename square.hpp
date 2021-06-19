#ifndef SQUARE_HPP
#define SQUARE_HPP


#include "intersectable.hpp"


#include "geom.hpp"
#include "hit.hpp"

#include "bitmap.hpp"


class Square : public Intersectable
{

    public:

    geom::vec3f p1;
    geom::vec3f p2;
    geom::vec3f p3;
    geom::vec3f p4;

    geom::vec3f v1;
    geom::vec3f v2;
    geom::vec3f v3;
    geom::vec3f v4;

    geom::vec3f n1;
    geom::vec3f n2;

    Square( geom::vec3f p1,
            geom::vec3f p2,
            geom::vec3f p4,
            geom::vec3f p3,
            const Material &material)
        : Intersectable(material)
        , checker_pattern_enable(false)
        , texture_enable(false)
    {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
        this->p4 = p4;

        v1 = p2 - p1;
        v2 = p3 - p1;

        v3 = p3 - p4;
        v4 = p2 - p4;

        n1 = cross(v1, v2).unit();
        n2 = cross(v3, v4).unit();
    }

    virtual
    ~Square()
    {

    }




    Hit Intersect(const Ray& ray);

    void SetCheckerPattern(bool enable);

    void apply_checker(const geom::vec3f &hit_position, Material &material_copy)
    {
        // set the color of the hit depending on the position
        geom::vec3f x_unit_vector = (p2 - p1).unit();
        float x_coord = dot(hit_position - p1, x_unit_vector);
        
        geom::vec3f y_unit_vector = cross(n1, x_unit_vector);
        float y_coord = dot(hit_position - p1, y_unit_vector);

        int x = (int)(x_coord / 0.5f); // TODO: change this to a member variable, it describes the size of the texture/checkerboard
        int y = (int)(y_coord / 0.5f); // same as above
        if((x + y) % 2 == 0)
        {
            material_copy.color *= 0.3f; // make darker
        }
        else
        {
            // do nothing to color
        }
    }

    void apply_texture(const geom::vec3f &hit_position, Material &material_copy)
    {
        // set the color of the hit depending on the position
        geom::vec3f x_unit_vector = (p2 - p1).unit();
        float x_coord = dot(hit_position - p1, x_unit_vector);
        
        geom::vec3f y_unit_vector = cross(n1, x_unit_vector);
        float y_coord = dot(hit_position - p1, y_unit_vector);

        int x = (int)(x_coord / 0.05f); // TODO: change this to a member variable, it describes the size of the texture/checkerboard
        int y = (int)(y_coord / 0.05f); // same as above
        
        if(x >= 0 && x < texture.width)
        {
            if(y >= 0 && y < texture.height)
            {
                unsigned char r, g, b;
                texture.GetPixel(x, y, r, g, b);
                float rr = (float)(r) / 255.f;
                float gg = (float)(g) / 255.f;
                float bb = (float)(b) / 255.f;
                material_copy.color = ColorWide(0.f, rr, gg, bb, 0.f);
            }
        }
    }


    void SetTexture(Bitmap &bitmap)
    {
        this->texture = bitmap;
        texture_enable = true;
    }


    private:

    bool checker_pattern_enable;
    bool texture_enable;
    Bitmap texture;

};



#endif // SQUARE_HPP