#include "scene.hpp"


#include "hit.hpp"
#include "color.hpp"
#include "material.hpp"
#include "triangle.hpp"
#include "square.hpp"
#include "sphere.hpp"


#include "precision_epsilon.hpp"



void Scene::Build()
{

    camera.SetFOVx(deg_to_rad(75.0f));
    camera.SetPosition(geom::vec3f(0.0f, 2.0f, 2.0f));
    //camera.SetLookAtDirection(geom::vec3f(0.f, 0.f, 0.f));
    camera.SetLookAtPosition(geom::vec3f(0.f, 0.f, 0.f));


    // set / change camera
    // default constructor currently used

    /*** add lights ***/

    ColorWide light_emission        (1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
    ColorWide light_emission_green  (0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    ColorWide light_emission_red    (0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    ColorWide light_emission_orange (0.0f, 1.0f, 0.3f, 0.0f, 0.0f);
    ColorWide light_emission_bulb   (0.0f, 1.0f, 0.85f, 0.65f, 0.0f);

    lights.push_back(new Light(light_emission));
    lights.back()->SetPosition(geom::vec3f(10.0f, 10.0f, 0.0f));
    lights.back()->intensity = 20.0f;

    lights.push_back(new Light(light_emission_green));
    lights.back()->SetPosition(geom::vec3f(-10.0f, -10.0f, 0.0f));
    lights.back()->intensity = 20.0f;

    lights.push_back(new Light(light_emission_red));
    lights.back()->SetPosition(geom::vec3f(10.0f, -10.0f, 0.0f));
    lights.back()->intensity = 20.0f;

    lights.push_back(new Light(light_emission_orange));
    lights.back()->SetPosition(geom::vec3f(-10.0f, 10.0f, 0.0f));
    lights.back()->intensity = 20.0f;

    lights.push_back(new Light(light_emission_bulb));
    lights.back()->SetPosition(geom::vec3f(0.0f, 24.5f, 0.0f));
    lights.back()->intensity = 50.0f;

    lights.push_back(new Light(light_emission_bulb));
    lights.back()->SetPosition(geom::vec3f(0.0f, 24.5f, 10.0f));
    lights.back()->intensity = 50.0f;

    lights.push_back(new Light(light_emission_bulb));
    lights.back()->SetPosition(geom::vec3f(0.0f, 24.5f, -10.0f));
    lights.back()->intensity = 50.0f;

    lights.push_back(new Light(light_emission_bulb));
    lights.back()->SetPosition(geom::vec3f(0.0f, 24.5f, 20.0f));
    lights.back()->intensity = 50.0f;

    lights.push_back(new Light(light_emission_bulb));
    lights.back()->SetPosition(geom::vec3f(0.0f, 24.5f, -20.0f));
    lights.back()->intensity = 50.0f;
    

    /*** create materials ***/
    Material diffuse_material;
    diffuse_material.SetThin(true, 0.1f);
    diffuse_material.color = ColorWide(0.0f, 1.0f, 0.1f, 0.1f, 0.0f);

    Material diffuse_material_white;
    diffuse_material_white.color = ColorWide(0.0f, 1.0f, 1.0f, 1.0f, 0.0f);

    Material diffuse_material_green;
    diffuse_material_green.color = ColorWide(0.0f, 0.0f, 1.0f, 0.0f, 0.0f);

    Material diffuse_material_red;
    diffuse_material_red.color = ColorWide(0.0f, 1.0f, 0.0f, 0.0f, 0.0f);

    Material diffuse_material_blue;
    diffuse_material_blue.color = ColorWide(0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    Material diffuse_material_white_thin;
    diffuse_material_white_thin.SetThin(true, 0.3f);
    diffuse_material_white_thin.color = ColorWide(0.0f, 1.0f, 1.0f, 1.0f, 0.0f);

    Material diffuse_material_grey;
    diffuse_material_grey.color = ColorWide(0.0f, 0.8f, 0.8f, 0.8f, 0.0f);


    /*** add objects ***/

    objects.push_back(new Sphere(   geom::vec3f(1.0f, 0.2f, 1.0f),
                                    0.1f, diffuse_material_white));

    objects.push_back(new Sphere(   geom::vec3f(1.0f, 0.2f, -1.0f),
                                    0.1f, diffuse_material_green));

    objects.push_back(new Sphere(   geom::vec3f(-1.0f, 0.2f, -1.0f),
                                    0.1f, diffuse_material_red));

    objects.push_back(new Sphere(   geom::vec3f(-1.0f, 0.2f, 1.0f),
                                    0.1f, diffuse_material_blue));

    objects.push_back(new Sphere(   geom::vec3f(0.0f, 0.2f, 0.0f),
                                    0.1f, diffuse_material_white));
    
    float tsize = 0.5f;
    float z = 5.0f;
    if(0)
    {
        objects.push_back(new Triangle( geom::vec3f(-tsize, -tsize, z),
                                        geom::vec3f(tsize, -tsize, z),
                                        geom::vec3f(tsize, tsize, z),
                                        diffuse_material/*mirror_material*/));
    }

    if(0)
    {
        objects.push_back(new Triangle( geom::vec3f(tsize, tsize, z),
                                        geom::vec3f(-tsize, tsize, z),
                                        geom::vec3f(-tsize, -tsize, z),
                                        diffuse_material/*mirror_material*/));
    }

    if(0)
    {
        objects.push_back(new Triangle( geom::vec3f(-3.0f, -3.0f, 6.0f),
                                        geom::vec3f(-3.0f, -0.0f, 6.0f),
                                        geom::vec3f(-0.0f, -3.0f, 6.0f),
                                        diffuse_material));

        objects.push_back(new Triangle( geom::vec3f( 0.0f, -2.0f, 6.0f),
                                        geom::vec3f(+1.0f, -2.0f, 6.0f),
                                        geom::vec3f( 0.0f, -1.0f, 6.0f),
                                        diffuse_material));
    }

    if(0)
    {
        objects.push_back(new Sphere(   geom::vec3f(1.5f, 1.5f, 10.0f),
                                        1.0f,
                                        diffuse_material_white));
    }

    if(0)
    {
        objects.push_back(new Sphere(   geom::vec3f(-1.5f, 1.5f, 10.0f),
                                        1.0f,
                                        diffuse_material_white_thin));
        lights.push_back(new Light(light_emission_bulb));
        lights.back()->SetPosition(geom::vec3f(-2.4f, 1.5f, 10.0f));
        lights.back()->intensity = 3.0f;
    }


    float cubesize = 40.0f;

    // back
    if(0)
    {
        objects.push_back(new Square(   geom::vec3f(-cubesize, -0.0f*cubesize, cubesize),
                                        geom::vec3f(+cubesize, -0.0f*cubesize, cubesize),
                                        geom::vec3f(+cubesize, +cubesize, cubesize),
                                        geom::vec3f(-cubesize, +cubesize, cubesize),
                                        diffuse_material_grey));
    }

    // front
    if(0)
    {
        objects.push_back(new Square(   geom::vec3f(-cubesize, -0.0f*cubesize, -cubesize),
                                        geom::vec3f(+cubesize, -0.0f*cubesize, -cubesize),
                                        geom::vec3f(+cubesize, +cubesize, -cubesize),
                                        geom::vec3f(-cubesize, +cubesize, -cubesize),
                                        diffuse_material_grey));
    }

    // top
    if(0)
    {
        objects.push_back(new Square(   geom::vec3f(-cubesize, +cubesize, +cubesize),
                                        geom::vec3f(+cubesize, +cubesize, +cubesize),
                                        geom::vec3f(+cubesize, +cubesize, -cubesize),
                                        geom::vec3f(-cubesize, +cubesize, -cubesize),
                                        diffuse_material_grey));
    }

    // bottom
    if(1)
    {

        objects.push_back(new Triangle( geom::vec3f(-cubesize, 0.01f, +cubesize),
                                        geom::vec3f(+cubesize, 0.01f, +cubesize),
                                        geom::vec3f(+cubesize, 0.01f, -cubesize),
                                        diffuse_material_grey));

        objects.push_back(new Square(   geom::vec3f(-cubesize, -0.0f*cubesize, +cubesize),
                                        geom::vec3f(+cubesize, -0.0f*cubesize, +cubesize),
                                        geom::vec3f(+cubesize, -0.0f*cubesize, -cubesize),
                                        geom::vec3f(-cubesize, -0.0f*cubesize, -cubesize),
                                        diffuse_material_grey));
        Square *the_square = dynamic_cast<Square*>(objects.back());
        the_square->SetCheckerPattern(true);
    }

    // Mario
    if(1)
    {
        float x1 = 0.0f;    float x2 = 1.0f;
        float z1 = 0.0f;    float z2 = -1.0f;
        float y = 0.02f;
        Square *the_mario_square = new Square(  geom::vec3f(x1, y, z1),
                                                geom::vec3f(x2, y, z1),
                                                geom::vec3f(x2, y, z2),
                                                geom::vec3f(x1, y, z2),
                                                diffuse_material_blue);
        the_mario_square->SetTexture(texture_map["mario"]);
        objects.push_back(the_mario_square);
    }

    // left
    if(0)
    {
        objects.push_back(new Square(   geom::vec3f(-cubesize, -0.0f*cubesize, -cubesize),
                                        geom::vec3f(-cubesize, -0.0f*cubesize, +cubesize),
                                        geom::vec3f(-cubesize, +cubesize, +cubesize),
                                        geom::vec3f(-cubesize, +cubesize, -cubesize),
                                        diffuse_material_grey));
    }

    // right
    if(0)
    {
        objects.push_back(new Square(   geom::vec3f(+cubesize, -0.0f*cubesize, -cubesize),
                                        geom::vec3f(+cubesize, -0.0f*cubesize, +cubesize),
                                        geom::vec3f(+cubesize, +cubesize, +cubesize),
                                        geom::vec3f(+cubesize, +cubesize, -cubesize),
                                        diffuse_material_grey));
        Square *the_square = dynamic_cast<Square*>(objects.back());
        the_square->SetCheckerPattern(true);
    }


    // TODO: thin material lighting calculation needs to work with 
    // normals on both sides of triangle face

}



void Scene::getFirstIntersect(Hit &nearest_hit, const Ray& ray)
{
    // TODO: put this somewhere else, perhaps in another file 
    // or as a global constant
    

    for(Intersectable *object: objects)
    {
        Hit current_hit = object->Intersect(ray);

        if(current_hit.valid)
        {
            if(current_hit.distance > precision_elipson)
            {
                if(!nearest_hit.valid ||
                    current_hit.distance < nearest_hit.distance)
                {
                    nearest_hit = current_hit;
                
                }
                else
                {
                    // hit is further away
                }
            }
            else
            {
                // cannot determine if the next hit is the same
                // as the previous one due to limited machine
                // precision
            }
        }
        else
        {
            // hit is not valid, do nothing
        }
    }
}


void Scene::Render(Bitmap &bitmap)
{

    std::cout << __func__ << std::endl;
    std::cout << "*** debug information ***" << std::endl;
    std::cout << camera << std::endl;
    std::cout << "" << std::endl;

    // operate shutter with 10 milliseconds
    //camera.Shutter(10000);

    //camera.GetScreen().SetPixelResolution(8, 6);
    std::cout << camera.GetScreen().GetAspectRatio() << std::endl;
    
    unsigned int num_pixels_x = 0;
    unsigned int num_pixels_y = 0;
    camera.GetScreen().GetNumPixels(num_pixels_x, num_pixels_y);

    std::cout << "Screen: " << num_pixels_x << " " << num_pixels_y << std::endl;

    bool debug = false;

    for(unsigned int y = 0; y < num_pixels_y; ++ y)
    {
        for(unsigned int x = 0; x < num_pixels_x; ++ x)
        {
            //std::cout << "x=" << x << " y=" << y << std::endl;
            
            Ray camera_ray = camera.GetRay(x, y);
            //std::cout << x << ", " << y << " : " << camera_ray.dir << std::endl;

            if(debug)
            {
                std::cout << "camera_ray" << std::endl;
                std::cout << camera_ray << std::endl;
            }
            
            ColorWide camera_radiance; // init to zero

            Hit nearest_hit;
            getFirstIntersect(nearest_hit, camera_ray);

            if(nearest_hit.valid)
            {
                if(debug)
                {
                    std::cout << "valid hit" << std::endl;
                    std::cout << "x=" << x << " y=" << y << std::endl;
                    std::cout << "position: " << nearest_hit.position << std::endl;
                    std::cout << "distance: " << nearest_hit.distance << std::endl;
                    std::cout << "normal: " << nearest_hit.normal << std::endl;
                }

                Material material = nearest_hit.material;
                if(material.type == MaterialType::DIFFUSE)
                {
                    if(debug)
                    {
                        std::cout << "material/diffuse" << std::endl;
                    }

                    // new class for flux?
                    ColorWide illumination; // init to zero

                    float cos_theta_camera_ray =
                        fcosangle(camera_ray.dir, nearest_hit.normal);
                    // the sign of cos(theta) is used to determine the transmission
                    // in the case of thin material
                    int sign_cos_theta_camera_ray = fsign(cos_theta_camera_ray);

                    // NOTE: for cos_theta_camera_ray: negative value means normal
                    // points towards the camera

                    // cos_theta_camera_ray can be positive, which means
                    // the surface normal points away from the camera
                    if(cos_theta_camera_ray > 0.0f)
                    {
                        // invert the normal and cos_theta_camera_ray
                        cos_theta_camera_ray = -cos_theta_camera_ray;
                        nearest_hit.normal = -nearest_hit.normal;

                        // invert the sign variable
                        sign_cos_theta_camera_ray = -sign_cos_theta_camera_ray;

                        // the normal now always points towards the camera
                        // and the variable cos_theta_camera_ray is always negative
                        // the sign variable is always negative
                    }

                    for(Light* light: lights)
                    {
                        // TODO: move this calculation into the Light class
                        if(light->type == LightType::OMNIDIRECTIONAL_POINT_SOURCE)
                        {
                            // vector connecting hit position to light position
                            // analagous to the light->direction used in below calculation
                            /*
                            vec3 dist = light->position - hit.position;
                            Ray shadowRay(hit.position + epsilon * hit.normal, dist);
                            float cosTheta = dot(hit.normal, dist);
                            float square_distance = dot(dist, dist);
                            */

                            if(debug)
                            {
                                std::cout << "light/omni" << std::endl;
                            }

                            Ray ray_to_light(nearest_hit.position, light->position);

                            // calculate cos(theta) and check that cos(theta) > 0
                            
                            // cos(theta) = vector_a . vector_b
                            // theta = angle between ray from hit to light
                            // and hit normal vector
                            float cos_theta = 
                                fcosangle(ray_to_light.dir, nearest_hit.normal);
                            int sign_cos_theta = fsign(cos_theta);

                            // if cos_theta is positive, then the light is
                            // incident on the same side as the camera ray


                            if(cos_theta > 0.0f ||
                                material.is_thin)
                            {

                                //cos_theta = fabs(cos_theta);

                                // if material is "thin" then light calculation for thin
                                // material should be done here. it is the same as the
                                // light calculation for the regular/"thick" material
                                // but modified by a scaling factor

                                float thin_scale_factor = 1.0f;
                                if(material.is_thin)
                                {
                                    //if(cos_theta >= 0.0f && cos_theta_camera_ray >= 0.0f)
                                    if(-sign_cos_theta == sign_cos_theta_camera_ray)
                                    {
                                        // incident light same side as emitted light
                                        thin_scale_factor =
                                            1.0f - material.thin_attenuation_factor;
                                    }
                                    else
                                    {
                                        // incident light opposite side of emitted light
                                        thin_scale_factor =
                                            material.thin_attenuation_factor;
                                    }

                                    //if(cos_theta < 0.0f) cos_theta = -cos_theta;
                                }

                                float abs_cos_theta = cos_theta;
                                if(abs_cos_theta < 0.0f) abs_cos_theta = -abs_cos_theta;

                                // TODO: move this check before checking
                                // if cos_theta > 0.0f || material.is_thin
                                Hit shadow_hit;
                                getFirstIntersect(shadow_hit, ray_to_light);
                                if(shadow_hit.valid &&
                                    shadow_hit.distance < ray_to_light.distance)
                                {
                                    // the light is obscured by an object

                                    /*
                                    std::cout << "obscured" << std::endl;
                                    std::cout << "distance = " << shadow_hit.distance << std::endl;
                                    std::cout << "ray_to_light.distance = " << ray_to_light.distance << std::endl;
                                    */

                                    // TODO: check if obscuring object is "thin", and perform
                                    // light calculation
                                    // Note: Don't do this. It will be weird to include
                                    // contribution from an obscuring thin object
                                    // but not nearby off-axis contributions from other thin
                                    // materials.
                                    // This requires a more advanced rendering algorithm
                                }
                                else
                                {
                                    // the light is not obscured by an object

                                    ColorWide lemission = light->emission;
                                    geom::vec3f lposition = light->position;
                                    float lintensity = light->intensity;

                                    // TODO: there are lots of ways to get this value
                                    float inv_distance_square = 1.0 /
                                        (ray_to_light.distance * ray_to_light.distance);

                                    ColorWide l = abs_cos_theta * lintensity * inv_distance_square * lemission;

                                    illumination += thin_scale_factor * l;
                                    // TODO Blinn-Phong Model ?
                                    // or a similar model for specular reflection modeling

                                    /*
                                    std::cout << "light not obscured" << std::endl;
                                    std::cout << "lemission=" << lemission << std::endl;
                                    std::cout << "lintensity=" << lintensity << std::endl;
                                    std::cout << "inv_distance_square=" << inv_distance_square << std::endl;

                                    std::cout << "cos_theta=" << cos_theta << std::endl;
                                    std::cout << "illumination=" << illumination << std::endl;
                                    std::cin.get();
                                    */
                                    
                                }
                                


                                    

                            }
                            else
                            {
                                // position of light is such that cos(theta) < 0
                                // and material is not a thin material
                            }

                        } // light Type
                        else
                        {
                            // light type logic is not implemented
                        }

                    } // for Light


                    // TODO: thin material modeling is bad
                    // should use factor alpha for transmission and
                    // reflect 1-alpha to conserve energy

                    // TODO: check cos theta camera ray sign, inverse of cos theta sign
                    // NOTE: no longer need to do this as cos_theta_camera_ray is now
                    // always negative

                    // TODO: should I include this factor of 1/r**2 ?
                    /*
                    float inv_distance_square_camera =
                        1.0 / (nearest_hit.distance * nearest_hit.distance);
                        */
                    // this factor not included because camera solid angle is
                    // proportional to r**2 hence these factors exactly cancel
                    
                    // TODO: move elsewhere
                    float camera_sensitivity_factor = 4.0f; //100.0f;

                    camera_radiance += 
                        camera_sensitivity_factor
                        * (-cos_theta_camera_ray) * illumination 
                        //* inv_distance_square_camera * material.color;
                        * material.color;
                    // TODO: should the material color be included in the light loop?

                    // testing
                    //camera_radiance = ColorWide(0.0f, 1.0f, 1.0f, 1.0f, 0.0f);

                }
                else
                {
                    // hit logic is not implemented for this material type
                }


                if(debug)
                {
                    std::cin.get();
                }


            }


            ColorWide pixel_color = camera_radiance;

            camera.GetScreen().SetPixel(x, y, pixel_color);

        }
    }


    bitmap = (Bitmap)camera.GetScreen();
}




