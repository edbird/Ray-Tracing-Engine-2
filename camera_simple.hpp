#ifndef CAMERA_SIMPLE_HPP
#define CAMERA_SIMPLE_HPP


#include "geom.hpp"
#include "screen.hpp"
#include "math_functions.hpp"
#include "ray.hpp"


#include <iostream>



class CameraSimple
{

    friend std::ostream& operator<<(std::ostream &os, const CameraSimple &camera);


    public:

    CameraSimple()
        : screen(800, 600)
        , position(0.0f, 0.0f, 0.0f)
        , up(0.0f, 1.0f, 0.0f)
        , right(1.0f, 0.0f, 0.0f)
        , lookat_direction(0.0f, 0.0f, -1.0f)
        , distance_to_screen(1.0f)
        , fov_x(deg_to_rad(60.0f))
        , tan_theta_x(std::tan(fov_x))
        , tan_theta_y(std::tan(fov_x * (800.f / 600.f)))
        , screen_relative_position(0.0, 0.0, -1.0f) // TODO: what happens if ray does not intersect screen?
    {

    }

    // TODO: fix these constructors
    CameraSimple(const unsigned int num_pixels_x, const unsigned int num_pixels_y)
        : screen(num_pixels_x, num_pixels_y)
        , position(0.0f, 0.0f, 0.0f)
        , up(0.0f, 1.0f, 0.0f)
        , right(1.0f, 0.0f, 0.0f)
        , lookat_direction(0.0f, 0.0f, -1.0f)
        , distance_to_screen(1.0f)
        , fov_x(deg_to_rad(60.0f))
        , tan_theta_x(std::tan(fov_x))
        , tan_theta_y(std::tan(fov_x * (num_pixels_x / num_pixels_y))) // TODO: num_pixels_y = 0 -> boom
        , screen_relative_position(0.0, 0.0, -1.0f)
    {
        
    }

/*
    CameraSimple(const geom::vec3f position)
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
    CameraSimple(
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
    ~CameraSimple()
    {

    }


    Screen& GetScreen()
    {
        return screen;
    }

    void SetPosition(const geom::vec3f &position)
    {
        this->position = position;
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


    void SetLookAtPosition(const geom::vec3f lookat_position);

    // this will invalidate the up and right vectors, but I have not fixed this
    void SetLookAtDirection(const geom::vec3f lookat_direction);
    //{
        // invalidates
        // up
        // right
        // lookat_direction
        // screen_relative_position



    //}

    void SetDistanceToScreen(float distance_to_screen)
    {
        // invalidates:
        // distance_to_screen
        // screen_relative_position

        this->distance_to_screen = distance_to_screen;
        this->screen_relative_position = distance_to_screen * this->lookat_direction;
    }

    void SetFOVx(float fov)
    {
        // invalidates:
        // fov_x
        // tan_theta_x
        // tan_theta_y

        this->fov_x = fov;
        float aspect_ratio = this->screen.GetAspectRatio();
        float theta_x = 0.5f * this->fov_x;
        float theta_y = 0.5f * this->fov_x * aspect_ratio;
        this->tan_theta_x = std::tan(theta_x);
        this->tan_theta_y = std::tan(theta_y);
    }

    // the orientation of the camera is set using the up and right vectors
    // the member up and member right vectors are set by this function
    // the member position remains unchanged
    // this invalidates the member variables:
    //      lookat_position
    //      lookat_direction
    //      screen_absolute_position
    //      screen_relative_position
    /*
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
        lookat_direction = geom::cross(this->up, this->right); //.unit();

        // set the absolute lookat position
        lookat_position = position + distance_to_lookat * lookat_direction;

        // set the relative and absolute screen coordinates
        screen_relative_position = distance_to_screen * lookat_direction;
        screen_absolute_position = position + screen_relative_position;

    }
    */
    // TODO ^

    Ray GetRay(int x, int y);


    private:

    Screen screen;


    geom::vec3f position;
    
    // the following 3 orientation vectors are an over-specification of the problem
    // they are all constrained to be unit vectors, and lookat_direction = cross(up, right)
    // TODO: this means that the lookat_direction (by default) is cross(x_unit, y_unit) = -z_unit
    // is this wrong?
    geom::vec3f up;
    geom::vec3f right;
    geom::vec3f lookat_direction; // unit vector in the direction the camera is pointing

    //
    float distance_to_screen;   // store the distance to the screen
    float fov_x;                // and the fov_x angle
                                // these 2 values imply the size/dimensions of
                                // the screen, which are not stored
    // stored for optimization
    float tan_theta_x;
    float tan_theta_y;
    // the relative position is stored for computation convenience / optimization
    geom::vec3f screen_relative_position; // vector to screen from eye: relative position of screen relative to eye
//    float focal_distance; // distance to focal point, might be used for some blur effect or something
    //float fov_y;

    // TODO: currently the FOV is stored/set and the size of the CCD (screen)
    // is calculated using the FOV and the distance to screen.
    // have an option to set using function calls with FOV, but store data
    // as calculated screen size and distance, then get FOV from these values
    // (actually FOV is not needed: FOV used in calculation of GetRay function
    // where we can instead use the screen dimensions instead)



};






#endif // CAMERA_SIMPLE_HPP