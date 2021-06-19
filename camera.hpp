#ifndef CAMERA_HPP
#define CAMERA_HPP


#include "geom.hpp"
#include "screen.hpp"
#include "math_functions.hpp"
#include "ray.hpp"


#include <iostream>



class Camera
{

    friend std::ostream& operator<<(std::ostream &os, const Camera &camera);


    public:

    Camera()
        : screen(800, 600)
        , position(0.0f, 0.0f, 0.0f)
        , up(0.0f, 1.0f, 0.0f)
        , right(1.0f, 0.0f, 0.0f)
        , lookat_position(0.0f, 0.0f, -2.0f)
        , lookat_direction(0.0f, 0.0f, -2.0f)
        , screen_absolute_position(0.0, 0.0, -1.0f) // TODO: this doesn't make sense, right cross up = negative z
        , screen_relative_position(0.0, 0.0, -1.0f) // TODO: what happens if ray does not intersect screen?
        , fov_x(deg_to_rad(60.0f))
    {

    }

    // TODO: fix these constructors
    Camera(const unsigned int num_pixels_x, const unsigned int num_pixels_y)
        : screen(num_pixels_x, num_pixels_y)
        , position(0.0f, 0.0f, 0.0f)
        , lookat_position(0.0f, 0.0f, -2.0f)
        , lookat_direction(0.0f, 0.0f, -2.0f)
        , screen_absolute_position(0.0, 0.0, -1.0f)
        , screen_relative_position(0.0, 0.0, -1.0f)
        , fov_x(deg_to_rad(60.0f))
    {
        
    }

/*
    Camera(const geom::vec3f position)
        : screen(800, 600)
        , position(position)
        , lookat_position(0.0f, 0.0f, 2.0f)
        , lookat_direction(0.0f, 0.0f, 2.0f)
        , screen_absolute_position(0.0, 0.0, 1.0f)
        , screen_relative_position(0.0, 0.0, 1.0f)
        //, focal_distance(1.0f)
    {
        // assumes a default distance to screen of 1.0f
        geom::vec3f look_direction = geom::cross(up, right).unit();
        this->screen_relative_position = look_direction;
        this->screen_absolute_position = position + look_direction;
    }
*/

/*
    Camera(
        const geom::vec3f position,
        const geom::vec3f up,
        const geom::vec3f lookat)
        : screen(800, 600)
        , position(position)
        , screen_absolute_position(0.0, 0.0, 1.0f)
        , screen_relative_position(0.0, 0.0, 1.0f)
    {

    }
*/

    virtual
    ~Camera()
    {

    }


    Screen& GetScreen()
    {
        return screen;
    }


    void SetFOVx(float fov)
    {
        this->fov_x = fov;
    }

    void SetPosition(const geom::vec3f &position)
    {
        geom::vec3f lookat_position_relative = lookat_position - this->position;

        this->position = position;
        this->lookat_position = position + lookat_position_relative;
        this->screen_absolute_position = position + this->screen_relative_position;


    }

/*
    geom::vec3f position;
    geom::vec3f up;
    geom::vec3f right;
    geom::vec3f lookat_position; // vector of absolute look at position
    geom::vec3f lookat_direction; // unit vector in the direction the camera is pointing
    geom::vec3f screen_absolute_position; // absolute position of screen
    geom::vec3f screen_relative_position; 
*/

    void SetLookAt(const geom::vec3f lookat);
    //void SetLookAt2(const geom::vec3f lookat);
    

    // this will invalidate the up and right vectors, but I have not fixed this
    /*void LookAt(const geom::vec3f lookat)
    {
        this->lookat_position = lookat;
        this->lookat_direction = (lookat - this->position).unit();

        std::cerr << "Error: the up and right vectors are now invalid" << std::endl;
    }*/

    // this will invalidate the up and right vectors, but I have not fixed this
    void SetLookAtDirection(const geom::vec3f lookat_direction)
                            /*const geom::vec3f &position,
                            const geom::vec3f &direction,
                            const geom::vec3f &up,
                            const geom::vec3f &right)*/
    {
        /*float distance_to_lookat = (this->lookat_position - this->position).length();
        this->lookat_direction = lookat_direction;
        this->lookat_position = this->position + distance_to_lookat * lookat_direction;

        std::cerr << "Error: the up and right vectors are now invalid" << std::endl;*/

        float distance_to_lookat = (this->lookat_position - this->position).length();
        geom::vec3f lookat_position = this->position + distance_to_lookat * lookat_direction;

        SetLookAt(lookat_position);
    }

    void SetScreenAbsolutePosition(const geom::vec3f screen_absolute_position)
    {
        this->screen_absolute_position = screen_absolute_position;
        this->screen_relative_position = screen_absolute_position - this->position;
    }

    void SetScreenRelativePosition(const geom::vec3f screen_relative_position)
    {
        this->screen_relative_position = screen_relative_position;
        this->screen_absolute_position = this->position + screen_relative_position;
    }

    // the orientation of the camera is set using the up and right vectors
    // the member up and member right vectors are set by this function
    // the member position remains unchanged
    // this invalidates the member variables:
    //      lookat_position
    //      lookat_direction
    //      screen_absolute_position
    //      screen_relative_position
    void SetOrientation(const geom::vec3f up, const geom::vec3f right)
    {
        // remember the current distance to screen and
        // distance to absolute lookat position vector
        float distance_to_screen = this->screen_relative_position.length();
        float distance_to_lookat = (this->lookat_position - this->position).length();
        
        // set the members: up and right
        this->up = up.unit();
        this->right = right.unit();

        // calculate the lookat direction unit vector using the members
        // up and right
        lookat_direction = geom::cross(up, right); //.unit();

        // set the absolute lookat position
        lookat_position = position + distance_to_lookat * lookat_direction;

        // set the relative and absolute screen coordinates
        screen_relative_position = distance_to_screen * lookat_direction;
        screen_absolute_position = position + screen_relative_position;

    }

    /*
    void SetPixelResolution(const unsigned int num_pixels_x, const unsigned int num_pixels_y)
    {
        pixels_x = num_pixels_x;
        pixels_y = num_pixels_y;
    }
    */

    Ray GetRay(int x, int y);


    private:

    Screen screen;

    // TODO: clean up / fix this class
    geom::vec3f position;
    geom::vec3f up;
    geom::vec3f right;
    geom::vec3f lookat_position; // vector of absolute look at position
    geom::vec3f lookat_direction; // unit vector in the direction the camera is pointing
    geom::vec3f screen_absolute_position; // absolute position of screen
    geom::vec3f screen_relative_position; // vector to screen from eye: relative position of screen relative to eye
//    float focal_distance; // distance to focal point, might be used for some blur effect or something
    float fov_x;
    //float fov_y;

    // TODO: currently the FOV is stored/set and the size of the CCD (screen)
    // is calculated using the FOV and the distance to screen.
    // have an option to set using function calls with FOV, but store data
    // as calculated screen size and distance, then get FOV from these values
    // (actually FOV is not needed: FOV used in calculation of GetRay function
    // where we can instead use the screen dimensions instead)

    /*
    unsigned int pixels_x;
    unsigned int pixels_y;
    */


};






#endif // CAMERA_HPP