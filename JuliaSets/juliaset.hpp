#ifndef JULIASET_HPP
#define JULIASET_HPP

#include "complexnumber.hpp"
class JuliaSet{

public:
    JuliaSet(ComplexNumber (*pFunction) (ComplexNumber),
             const double min_x, const double max_x,
             const double min_y, const double max_y,
             const int n_xpixels, const int n_ypixels);

    int iterateMap(const ComplexNumber& z0);
    void Draw(const std::string fileName);

private:

    JuliaSet();

    // Corner positions
    double _min_x;
    double _min_y;
    double _max_x;
    double _max_y;

    // Number of pixels in the x and y direction
    int _n_xpixels;
    int _n_ypixels;

    // Pixel colour
    int _pixel_colour;

    // Its Function
    ComplexNumber  (*_f) (ComplexNumber);

    int recIterateMap(const ComplexNumber& z0, int pixel_colour,
                      ComplexNumber (*function) (ComplexNumber));

};

#endif // JULIASET_HPP
