#include <iostream>
#include <string>
#include "complexnumber.hpp"
#include "juliaset.hpp"

ComplexNumber Quadratic(const ComplexNumber z);

int main(){
    std::string cwd = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/JuliaSets/";
    // Instantiate Drawer
    // JuliaSet* drawer = new JuliaSet(Quadratic,-1.3,1.3,-1.3,1.3,2000,2000);
    // drawer->Draw("c_0.37_0.16.pgm");
    JuliaSet* drawer = new JuliaSet(Quadratic,-1.5,1.5,-1.5,1.5,2000,2000);
    drawer->Draw(cwd+"c_-0.75_0.25.pgm");

}

ComplexNumber Quadratic(const ComplexNumber z){
    double im = .65;
    ComplexNumber c(0, im);
    ComplexNumber result = z.CalculatePower(2.0) + c;
    return result;
}
