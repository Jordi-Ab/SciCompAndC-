
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include "juliaset.hpp"

JuliaSet::JuliaSet(ComplexNumber (*pFunction) (ComplexNumber),
                   const double min_x, const double max_x,
                   const double min_y, const double max_y,
                   const int n_xpixels, const int n_ypixels){

    // Corner positions
    _min_x = min_x; _max_x = max_x;
    _min_y = min_y; _max_y = max_y;

    // Number of pixels
    _n_xpixels = n_xpixels;
    _n_ypixels = n_ypixels;

    // Pixel Color starts at white.
    _pixel_colour = 255;

    // Pointer to function
    _f = pFunction;
}


JuliaSet::JuliaSet(){

}

// Drawing function
void JuliaSet::Draw(const std::string fileName){

    // Compute pixel resolution
    double x_step_size = (_max_x - _min_x)/(_n_xpixels-1);
    double y_step_size = (_max_y - _min_y)/(_n_ypixels-1);

    // Open file
    std::ofstream output_file;
    output_file.setf(std::ios::scientific,std::ios::floatfield);
    output_file.precision(6);

    // Print format header
    output_file.open(fileName.c_str());
    assert(output_file.is_open());
    output_file << "P2" << std::endl;
    output_file << "# Julia Set image" << std::endl;
    output_file << _n_xpixels << " " << _n_ypixels << std::endl;
    output_file << " 255" << std::endl;

    // For each pixel
    for(int i=0; i<_n_xpixels; i++){
        for(int j=0; j<_n_ypixels; j++){

            // Compose initial value for z
            ComplexNumber z0(_min_x + i*x_step_size, _min_y + j*y_step_size);

            // Iterate map and write on file
            output_file << std::setw(4) << iterateMap(z0);

        }
    // End of row, change line
    output_file << std::endl;
    }

    // Close file
    output_file.close();

}

/*
int JuliaSet::iterateMap(const ComplexNumber& z0){
      ComplexNumber z = z0;
      return recIterateMap(z, 255, this->_f);
}

int recIterateMap(const ComplexNumber& z0, int pixel_colour,
                  ComplexNumber (*function) (ComplexNumber)){
    if (z0.CalculateModulus()>=10.0 || pixel_colour<5){
        return pixel_colour;
    }else{
        z0 = (*function)(z0);
        return recIterateMap(z0, pixel_colour-5, function);
    }
}*/

int JuliaSet::iterateMap(const ComplexNumber& z0)
{

  // Copy initial value (z will be overwritten)
  ComplexNumber z = z0;

  // Pixels are initially white
  int pixel_colour = 255;

  // Iterate forward (for stopping criteria see slides)
  while ( z.CalculateModulus() < 10.0 && pixel_colour >= 5 )
  {

    // Iterate the map once
    z = (*_f)(z);

    // Change pixel colour
    pixel_colour -= 5;

  }

  return pixel_colour;

}
