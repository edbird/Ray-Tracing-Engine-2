#ifndef MATH_FUNCTIONS_HPP
#define MATH_FUNCTIONS_HPP


float deg_to_rad(float deg);

float rad_to_deg(float rad);

int fsign(float x);

int fclamp_to_int(float x, int min, int max);
int fclamp_log_to_int(float x, int min, int max);

#endif // MATH_FUNCTIONS_HPP