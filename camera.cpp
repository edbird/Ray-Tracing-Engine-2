#include "camera.hpp"



Ray Camera::GetRay(int x, int y)
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

    geom::vec3f vector_to_screen = screen_relative_position;

    float aspect_ratio = this->screen.GetAspectRatio();

    // TODO: optimize by storing only tan_theta_x, tan_theta_y
    float theta_x = 0.5f * fov_x;
    float theta_y = 0.5f * fov_x * aspect_ratio;
    float tan_theta_x = std::tan(theta_x);
    float tan_theta_y = std::tan(theta_y);

    // half the length of the sensor - the distance from the center to the
    // top edge or the right edge
    float distance_to_screen = screen_relative_position.length();
    float sensor_half_length_x = distance_to_screen * tan_theta_x;
    float sensor_half_length_y = distance_to_screen * tan_theta_y;

    // up and right are unit vectors
    // ff_x and ff_y are numbers in the range [+1, -1]
    geom::vec3f screen_center_to_pixel_up = ff_y * sensor_half_length_y * up;
    geom::vec3f screen_center_to_pixel_right = ff_x * sensor_half_length_x * right;
    geom::vec3f screen_center_to_pixel = screen_center_to_pixel_up + screen_center_to_pixel_right;

    // relative vector from position to center of pixel (x, y) on screen
    geom::vec3f direction = vector_to_screen + screen_center_to_pixel;
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


std::ostream& operator<<(std::ostream &os, const Camera &camera)
{
    std::cout << "> camera" << std::endl;
    std::cout << ">   pos: " << camera.position << std::endl;
    std::cout << ">   up: " << camera.up << std::endl;
    std::cout << ">   right: " << camera.right << std::endl;
    std::cout << ">   lookat pos: " << camera.lookat_position << std::endl;
    std::cout << ">   lookat dir: " << camera.lookat_direction << std::endl;
    std::cout << ">   screen a pos: " << camera.screen_absolute_position << std::endl;
    std::cout << ">   screen r pos: " << camera.screen_relative_position << std::endl;

    return os;
}

#if 0
// TODO: remove this
void Camera::SetLookAt2(
    //const geom::vec3f position,
    const geom::vec3f lookat//,
    //const geom::vec3f up,
    //const geom::vec3f right
    )
{
    // TODO: optimize this by retaining all "old" values before setting
    // new values at end of function, and storing all new values in
    // local variables rather than storing the old values in local vectors

    // retain the old lookat relative vector for calculation if required
    geom::vec3f previous_lookat_relative = this->lookat_position - this->position;

    this->lookat = lookat;
    geom::vec3f lookat_relative = lookat - this->position;
    this->lookat_direction = lookat_relative.unit();

    // this is the same as ProjectXZ()
    geom::vec3f lookat_relative_flat = lookat_relative.ProjectXZ(); // CrushY()

    // this will blow up if the projected length is 0
    //geom::vec3f lookat_relative_flat_unit = lookat_relative_flat.unit();
    geom::vec3f lookat_relative_flat_unit;
    float cos_phi = 0.0f;
    float sin_phi = 0.0f;
    if(geom::unit_safe(lookat_relative_flat_unit, lookat_relative_flat) == 0)
    {
        // no error
        cos_phi = lookat_relative_flat_unit.z;
        sin_phi = lookat_relative_flat_unit.x;
    }
    else
    {
        // project XZ
        geom::vec3f previous_lookat_relative_flat = previous_lookat_relative.ProjectXZ();

        // the rotation of the camera about the y axis is not determined,
        // retain the previous value, if the previous value is determined
        geom::vec3f previous_lookat_relative_flat_unit;
        float previous_cos_phi = 0.0f;
        float previous_sin_phi = 0.0f;
        if(geom::unit_safe(previous_lookat_relative_flat_unit, previous_lookat_relative_flat) == 0)
        {
            previous_cos_phi = previous_lookat_relative_flat_unit.z;
            previous_sin_phi = previous_lookat_relative_flat_unit.x;
        }
        else
        {
            // the rotation of the camera about the y axis before the new
            // lookat vector is applied was also not determinte... use
            // a default value of 0.0f

            // default value already set on initialization
        }

        cos_phi = previous_cos_phi;
        sin_phi = previous_sin_phi;
    }

    float D_y = lookat_direction.y;
    float D_xy = std::sqrt(1.0f - D_y * D_y);
    float cos_theta = D_y;
    float sin_theta = D_xy;
    float n_y = cos_theta;
    float n_xy = sin_theta;

    float n_x = sin_theta * sin_phi;
    float n_z = sin_theta * cos_phi;

    geom::vec3f next_up(n_x, n_y, n_z);

    geom::vec3f right = geom::cross(next_lookat_dir, next_up);

}
#endif

// TODO: check this
void Camera::SetLookAt(
    //const geom::vec3f position,
    const geom::vec3f lookat//,
    //const geom::vec3f up,
    //const geom::vec3f right
    )
{

    geom::vec3f next_lookat = lookat;

    // calculate new lookat relative vector and direction vector
    geom::vec3f next_lookat_relative = next_lookat - this->position;
    geom::vec3f next_lookat_direction = next_lookat_relative.unit();

    // this is the same as ProjectXZ()
    geom::vec3f next_lookat_relative_flat = next_lookat_relative.ProjectXZ(); // CrushY()

    // this will blow up if the projected length is 0
    //geom::vec3f lookat_relative_flat_unit = lookat_relative_flat.unit();
    geom::vec3f next_lookat_relative_flat_unit;
    float cos_phi = 0.0f;
    float sin_phi = 0.0f;
    if(geom::unit_safe(next_lookat_relative_flat_unit, next_lookat_relative_flat) == 0)
    {
        // no error
        cos_phi = next_lookat_relative_flat_unit.z;
        sin_phi = next_lookat_relative_flat_unit.x;
    }
    else
    {

        geom::vec3f previous_lookat = this->lookat_position;

        // retain the old lookat relative vector
        geom::vec3f previous_lookat_relative = previous_lookat - this->position;

        // project XZ
        geom::vec3f previous_lookat_relative_flat = previous_lookat_relative.ProjectXZ();

        // the rotation of the camera about the y axis is not determined,
        // retain the previous value, if the previous value is determined
        geom::vec3f previous_lookat_relative_flat_unit;
        //float previous_cos_phi = 0.0f;
        //float previous_sin_phi = 0.0f;
        if(geom::unit_safe(previous_lookat_relative_flat_unit, previous_lookat_relative_flat) == 0)
        {
            //previous_cos_phi = previous_lookat_relative_flat_unit.z;
            //previous_sin_phi = previous_lookat_relative_flat_unit.x;

            cos_phi = previous_lookat_relative_flat_unit.z;
            sin_phi = previous_lookat_relative_flat_unit.x;
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

        //next_cos_phi = previous_cos_phi;
        //next_sin_phi = previous_sin_phi;
    }

    float D_y = next_lookat_direction.y;
    //float D_xy = std::sqrt(1.0f - D_y * D_y);
    float D_xy = next_lookat_direction.length();
    float cos_theta = D_y;
    float sin_theta = D_xy;
    float n_y = cos_theta;
    float n_xy = sin_theta;

    float n_x = sin_theta * sin_phi;
    float n_z = sin_theta * cos_phi;

    geom::vec3f next_up(n_x, n_y, n_z);
    geom::vec3f next_right = geom::cross(next_lookat_direction, next_up);



    //this->lookat = next_lookat;
    this->up = next_up;
    this->right = next_right;
    this->lookat_position = next_lookat;
    this->lookat_direction = next_lookat_direction;

}