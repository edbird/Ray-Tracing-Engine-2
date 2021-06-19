

/*
 * References:
 *
 * https://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage
 * https://en.cppreference.com/w/cpp/thread/thread/thread#Notes
 * https://en.cppreference.com/w/cpp/utility/functional/ref
 *
 * https://taylorpetrick.com/blog/post/convolution-part3
 * https://en.wikipedia.org/wiki/Kernel_(image_processing)
 * https://upload.wikimedia.org/wikipedia/commons/3/3f/Bikesgray.jpg
 * https://en.wikipedia.org/wiki/Edge_detection
 *
 */



#include "bitmap.hpp"
#include "geom.hpp"



#include <iostream>
#include <fstream>



// if a ray travels further than this distance, we will exit a loop
const float finite_distance_limit = 100.0f;


#include "ray.hpp"









#include "light.hpp"
#include "scene.hpp"



#include <cmath>

#include "math_functions.hpp"




// TODO: MC version

int main(int argc, char* argv[])
{

    /*
    std::cout << "cross product tests" << std::endl;

    geom::vec3f i(1.0f, 0.0f, 0.0f);
    geom::vec3f j(0.0f, 1.0f, 0.0f);
    geom::vec3f k(0.0f, 0.0f, 1.0f);

    geom::vec3f i_cross_j = cross(i, j);
    geom::vec3f i_cross_k = cross(i, k);

    geom::vec3f j_cross_i = cross(j, i);
    geom::vec3f j_cross_k = cross(j, k);

    geom::vec3f k_cross_i = cross(k, i);
    geom::vec3f k_cross_j = cross(k, j);

    std::cout << "i = " << i << std::endl;
    std::cout << "j = " << j << std::endl;
    std::cout << "k = " << k << std::endl;
    std::cout << "i_cross_j = " << i_cross_j << std::endl;
    std::cout << "i_cross_k = " << i_cross_k << std::endl;
    std::cout << "j_cross_i = " << j_cross_i << std::endl;
    std::cout << "j_cross_k = " << j_cross_k << std::endl;
    std::cout << "k_cross_i = " << k_cross_i << std::endl;
    std::cout << "k_cross_j = " << k_cross_j << std::endl;

    std::cin.get();
    */
    

    Bitmap mario_bitmap;
    std::string path_mario("./res/mario.bmp");
    mario_bitmap.Read(path_mario);

    std::string path_mario_out_1("./res/mario1.bmp");
    mario_bitmap.Write(path_mario_out_1);

    std::cout << "bitmap.height=" << mario_bitmap.height
              << " bitmap.width=" << mario_bitmap.width << std::endl;
    for(int j = 0; j < mario_bitmap.height; ++ j)
    {
        for(int i = 0; i < mario_bitmap.width; ++ i)
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            mario_bitmap.GetPixel(i, j, r, g, b);

            if(r == 0 && g == 255 && b == 0)
            {
                g = 0;
                mario_bitmap.SetPixel(i, j, r, g, b);
            }
        }
    }

    std::string path_mario_out = "./res/mario_out.bmp";
    std::cout << "Writing bitmap image to file: " << path_mario_out << std::endl;
    mario_bitmap.Write(path_mario_out);


    ////////////////////////////////////////////////////////////////////////////
    // do some raytracing
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "Render begin" << std::endl;

    Scene scene;
    scene.RegisterTexture("mario", mario_bitmap);
    scene.Build();

    //Bitmap bitmap;
    Bitmap bitmap_output;// = (Bitmap)scene.camera.GetScreen();
    scene.Render(bitmap_output);

    bitmap_output.Write("render.bmp");

/*
    Eye eye;
    eye.SetPos(geom::vec3f(0.0f, 0.0f, 0.0f));
    eye.SetDir(geom::vec3f(0.0f, 0.0, -1.0f));
*/

/*
    Camera camera;

    bitmap screen_data(800, 600);
    geom::vec3f screen_center_pos(0.0f, 0.0f, -1.0f);
    float aspect_ratio = (float)screen.width / (float)screen.height;
    float field_of_view = degToRad(80.0f);

    // TODO: make multithread
    for(int j = 0; j < screen.height; j ++)
    {
        for(int i = 0; i < screen.width; ++ i)
        {

            Ray ray = camera.GetRay(i, j);
            ColorWide psd = ray.Trace();


            geom::vector3f vector_to_screen = screen_center_pos - eye.GetPos();

            Ray ray;
            ray.SetPos(eye.GetPos());

            // angle between the middle of the screen and the X edge
            float theta = 0.5f * field_of_view;

            float angle_x = (float)i - 0.5f * (float)screen.width;

            // it's a bit late in the evening to be doing geometry
            // let's resume another time...
            //
            // see you later - at some point I will start streaming on
            // Twitch as well - I have a feeling this will be a better platform
            // anyway
            //
            // 

            float x = (float);
            float y = ;

            geom::vec3f direction = vector_to_screen + screen_vector;
        }
    }

*/

    return 0;
}