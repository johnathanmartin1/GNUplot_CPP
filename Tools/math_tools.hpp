#ifndef MATH_TOOLS
#define MATH_TOOLS

#include <cmath>

double round_to_places(double value, int places)
{
    double scale = std::pow(10.0, places);

    return std::round(value * scale) / scale;
}



#endif