#include "camera_simple.hpp"



Ray CameraSimple::GetRay(int x, int y)
{
    // assumes that x, y are in range [0, WIDTH-1], [0, HEIGHT-1]
    // but they don't have to be

    unsigned int u_pixels_x = 0;
    unsigned int u_pixels_y = 0;
    this->screen.GetNumPixels(u_pixels_x, u_pixels_y);

    int pixels_x = (int)u_pixels_x; //(int)this->pixels_x;
    int pixels_y = (int)u_pixels_y; //(int)this->pixels_y;


    // fractional position on screen between [0.0, 1.0]
    // represents fractional position of center of pixel in image coordinates
    float f_x = ((float)x + 0.5f) / (float)pixels_x;
    float f_y = ((float)y + 0.5f) / (float)pixels_y;

    // fractional factor: multiply real world axis length of screen by this
    // factor to find scale factor for vectors right and up
    float ff_x = 2.0f * f_x - 1.0f;
    float ff_y = 2.0f * f_y - 1.0f;

    //geom::vec3f vector_to_screen = screen_relative_position;

    float aspect_ratio = this->screen.GetAspectRatio();

    // TODO: optimize by storing only tan_theta_x, tan_theta_y
    /*float theta_x = 0.5f * fov_x;
    float theta_y = 0.5f * fov_x * aspect_ratio;
    float tan_theta_x = std::tan(theta_x);
    float tan_theta_y = std::tan(theta_y);*/

    // half the length of the sensor - the distance from the center to the
    // top edge or the right edge
    /*float distance_to_screen = screen_relative_position.length();*/
    float sensor_half_length_x = distance_to_screen * tan_theta_x;
    float sensor_half_length_y = distance_to_screen * tan_theta_y; // TODO make these member variables

    // up and right are unit vectors
    // ff_x and ff_y are numbers in the range [+1, -1]
    geom::vec3f screen_center_to_pixel_up = ff_y * sensor_half_length_y * up;
    geom::vec3f screen_center_to_pixel_right = ff_x * sensor_half_length_x * right;
    geom::vec3f screen_center_to_pixel = screen_center_to_pixel_up + screen_center_to_pixel_right;

    // relative vector from position to center of pixel (x, y) on screen
    //geom::vec3f direction = vector_to_screen + screen_center_to_pixel;
    geom::vec3f direction = screen_relative_position + screen_center_to_pixel;
    direction.normalize();
    //geom::vec3f ray = position + vector_to_screen + screen_center_to_pixel;

/*
    std::cout << __func__ << std::endl;
    std::cout << x << " " << y << std::endl;
    std::cout << "f_x/y: " << f_x << " " << f_y << std::endl;
    std::cout << "theta: " << theta_x << " " << theta_y << std::endl;
    std::cout << "sensor length: " << sensor_half_length_x << " " << sensor_half_length_y << std::endl;
    std::cout << "up: " << screen_center_to_pixel_up << std::endl;
    std::cout << "right: " << screen_center_to_pixel_right << std::endl;
    std::cout << "pixel: " << screen_center_to_pixel << std::endl;
*/

    Ray ray;
    ray.SetStart(this->position);
    ray.SetDirection(direction);
    // do not set the end
    return ray;

}


std::ostream& operator<<(std::ostream &os, const CameraSimple &camera)
{
    std::cout << "> camera" << std::endl;
    std::cout << ">   pos: " << camera.position << std::endl;
    std::cout << ">   up: " << camera.up << std::endl;
    std::cout << ">   right: " << camera.right << std::endl;
    std::cout << ">   lookat: " << camera.lookat_direction << std::endl;
    std::cout << ">   distance_to_screen: " << camera.distance_to_screen << std::endl;
    std::cout << ">   fov x: " << camera.fov_x << std::endl;
    std::cout << ">   screen r pos: " << camera.screen_relative_position << std::endl;

    return os;
}


void CameraSimple::SetLookAtPosition(const geom::vec3f lookat_position)
{
    geom::vec3f lookat_direction = lookat_position - this->position;
    // will be normalized in function call

    SetLookAtDirection(lookat_direction);
}

/*
void CameraSimple::SetLookAtDirection(const geom::vec3f lookat_direction)
{ 
    // invalidates
    // up
    // right
    // lookat_direction
    // screen_relative_position


    // ensure the lookat direction is a unit vector, copy to local
    geom::vec3f next_lookat_direction = lookat_direction.unit();
    std::cout << "next_lookat_direction=" << next_lookat_direction << std::endl;

    // this is the same as ProjectXZ() / CrushY()
    // take only the XZ components
    geom::vec3f next_lookat_direction_projected = next_lookat_direction.ProjectXZ(); // CrushY()
    std::cout << "next_lookat_direction_projected=" << next_lookat_direction_projected << std::endl;

    // if Z, X components are 0 the phi angle is indeterminate
    // this will blow up if the projected length is 0
    //geom::vec3f lookat_relative_flat_unit = lookat_relative_flat.unit();
    // instead we take this approach:
    // compute the sin and cosine of the angle theta from the y unit vector
    float cos_theta = next_lookat_direction_projected.length();
    float sin_theta = next_lookat_direction.y;
    std::cout << "cos_theta=" << cos_theta << std::endl;
    std::cout << "sin_theta=" << sin_theta << std::endl;

    std::cout << "theta=" << rad_to_deg(std::acos(cos_theta)) << std::endl;
    std::cout << "theta=" << rad_to_deg(std::asin(sin_theta)) << std::endl;

    geom::vec3f next_lookat_direction_projected_unit;
    float cos_phi = 0.0f;
    float sin_phi = 0.0f;
    if(geom::unit_safe(next_lookat_direction_projected_unit, next_lookat_direction_projected) == 0)
    {
        // no error
        cos_phi = next_lookat_direction_projected_unit.z;
        sin_phi = next_lookat_direction_projected_unit.x;
        std::cout << "cos_phi=" << cos_phi << std::endl;
        std::cout << "sin_phi=" << sin_phi << std::endl;
    }
    else
    {

        geom::vec3f previous_lookat_direction = this->lookat_direction;

        // project XZ
        geom::vec3f previous_lookat_direction_projected = previous_lookat_direction.ProjectXZ();

        // the rotation of the camera about the y axis is not determined,
        // retain the previous value, if the previous value is determined
        geom::vec3f previous_lookat_direction_projected_unit;
        if(geom::unit_safe(previous_lookat_direction_projected_unit, previous_lookat_direction_projected) == 0)
        {
            cos_phi = previous_lookat_direction_projected_unit.z;
            sin_phi = previous_lookat_direction_projected_unit.x;
        }
        else
        {
            // the rotation of the camera about the y axis before the new
            // lookat vector is applied was also not determinte... use
            // a default value of 0.0f

            // default value already set on initialization
            cos_phi = 0.f;
            sin_phi = 0.f;
        }
    }

    std::cout << "phi=" << rad_to_deg(std::acos(cos_phi)) << std::endl;
    std::cout << "phi=" << rad_to_deg(std::asin(sin_phi)) << std::endl;

    float n_y = cos_theta;
    float n_z = sin_theta * cos_phi;
    float n_x = sin_theta * sin_phi;

    geom::vec3f next_up(n_x, n_y, n_z);
    std::cout << "next_up=" << next_up << std::endl;
    std::cout << "next_up.length()=" << next_up.length() << std::endl;
    geom::vec3f next_right = geom::cross(next_lookat_direction, next_up); // TODO: this obtains wrong direction of unit vector?
    std::cout << "next_right=" << next_right << std::endl;
    std::cout << "next_right.length()=" << next_right.length() << std::endl;


    this->up = next_up;
    this->right = next_right;
    this->lookat_direction = next_lookat_direction;

    // set the relative screen position
    this->screen_relative_position = distance_to_screen * next_lookat_direction;

}
*/

void CameraSimple::SetLookAtDirection(const geom::vec3f lookat_direction)
{ 
    // invalidates
    // up
    // right
    // lookat_direction
    // screen_relative_position


    // ensure the lookat direction is a unit vector, copy to local
    geom::vec3f next_lookat_direction = lookat_direction.unit();
    std::cout << "next_lookat_direction=" << next_lookat_direction << std::endl;

    // this is the same as ProjectXZ() / CrushY()
    // take only the XZ components
    geom::vec3f next_lookat_direction_projected = next_lookat_direction.ProjectXZ(); // CrushY()
    std::cout << "next_lookat_direction_projected=" << next_lookat_direction_projected << std::endl;

    // if Z, X components are 0 the phi angle is indeterminate
    // this will blow up if the projected length is 0
    //geom::vec3f lookat_relative_flat_unit = lookat_relative_flat.unit();
    // instead we take this approach:
    // compute the sin and cosine of the angle theta from the y unit vector
    float cos_theta = next_lookat_direction.y;
    float sin_theta = next_lookat_direction_projected.length();
    std::cout << "cos_theta=" << cos_theta << std::endl;
    std::cout << "sin_theta=" << sin_theta << std::endl;

    std::cout << "theta=" << rad_to_deg(std::acos(cos_theta)) << std::endl;
    std::cout << "theta=" << rad_to_deg(std::asin(sin_theta)) << std::endl;

    geom::vec3f next_lookat_direction_projected_unit;
    float cos_phi = 0.0f;
    float sin_phi = 0.0f;
    if(geom::unit_safe(next_lookat_direction_projected_unit, next_lookat_direction_projected) == 0)
    {
        // no error
        cos_phi = next_lookat_direction_projected_unit.z;
        sin_phi = next_lookat_direction_projected_unit.x;
        std::cout << "cos_phi=" << cos_phi << std::endl;
        std::cout << "sin_phi=" << sin_phi << std::endl;
    }
    else
    {

        geom::vec3f previous_lookat_direction = this->lookat_direction;

        // project XZ
        geom::vec3f previous_lookat_direction_projected = previous_lookat_direction.ProjectXZ();

        // the rotation of the camera about the y axis is not determined,
        // retain the previous value, if the previous value is determined
        geom::vec3f previous_lookat_direction_projected_unit;
        if(geom::unit_safe(previous_lookat_direction_projected_unit, previous_lookat_direction_projected) == 0)
        {
            cos_phi = previous_lookat_direction_projected_unit.z;
            sin_phi = previous_lookat_direction_projected_unit.x;
        }
        else
        {
            // the rotation of the camera about the y axis before the new
            // lookat vector is applied was also not determinte... use
            // a default value of 0.0f

            // default value already set on initialization
            cos_phi = 0.f;
            sin_phi = 0.f;
        }
    }

    std::cout << "phi=" << rad_to_deg(std::acos(cos_phi)) << std::endl;
    std::cout << "phi=" << rad_to_deg(std::asin(sin_phi)) << std::endl;

    // new vector which I imagined in my head
    float n_x = -cos_theta * sin_phi;
    float n_y = sin_theta;
    float n_z = -cos_theta * cos_phi;

    geom::vec3f next_up(n_x, n_y, n_z);
    std::cout << "next_up=" << next_up << std::endl;
    std::cout << "next_up.length()=" << next_up.length() << std::endl;

    geom::vec3f next_right = geom::cross(next_lookat_direction, next_up); // TODO: this obtains wrong direction of unit vector?
    std::cout << "next_right=" << next_right << std::endl;
    std::cout << "next_right.length()=" << next_right.length() << std::endl;

    // new vector which I imagined in my head
    float r_x = -cos_phi;
    float r_y = 0.0f;
    float r_z = sin_phi;

    geom::vec3f other_next_right(r_x, r_y, r_z);
    std::cout << "other_next_right=" << next_right << std::endl;
    std::cout << "other_next_right.length()=" << next_right.length() << std::endl;

    this->up = next_up;
    this->right = next_right;
    this->lookat_direction = next_lookat_direction;

    // set the relative screen position
    this->screen_relative_position = distance_to_screen * next_lookat_direction;

}
