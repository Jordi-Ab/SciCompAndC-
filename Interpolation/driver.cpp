#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <assert.h>
#include "Interpolant.hpp"
#include "VecsAndMats.hpp"
#include "myRandom.hpp"

std::string const DATA_PATH = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Interpolation/Graphs and Data/Data";

double* linspace(double low, double high, int n);
double* f(double* xs, int size);
double* runge_f(double* xs, int size);
double* sin_f(double* xs, int size);
void saveData(const std::string file_name, const double* x, const double* y, int n);
double* pointwiseError(double* comp_sol, double* true_sol, int n);
double* perturbValues(double* values, int size);
void testRungePhenom();
void perturbationAnalysis();
void Q2();
void chebyshevInterpolation();


int main(){

    //Q2();
    //testRungePhenom();
    //perturbationAnalysis();
    chebyshevInterpolation();

}

double* linspace(double low, double high, int n){
    double* range = new double[n];
    double h = (high - low)/(n-1);
    range[0] = low;
    for (int i=1; i<n-1; i++){
        range[i] = range[i-1] + h;
    }
    range[n-1] = high;
    return range;
}

double* chebyshevNodes(double low, double high, int n){
    double* range = new double[n+1];
    range[0] = low;
    for (int i=1; i<n; i++){
        range[i] = ((high + low)/2) - ((high - low)/2)*cos(i*M_PI/n);
    }
    range[n] = high;
    return range;
}

double* f(double* xs, int size){
    double* result = new double[size];
    for (int i=0; i<size; i++){
        result[i] = (pow(xs[i], 3) + 3*pow(xs[i], 2) - 6*xs[i] - 8)/4;
    }
    return result;
}

double* runge_f(double* xs, int size){
    double* result = new double[size];
    for (int i=0; i<size; i++){
        result[i] = 1/(1 + pow(xs[i], 2));
    }
    return result;
}

double* sin_f(double* xs, int size){
    double* result = new double[size];
    for (int i=0; i<size; i++){
        result[i] = sin(2*M_PI*xs[i]);
    }
    return result;
}

void saveData(const std::string file_name, const double* x, const double* y, int n){

    // Setting strem file precision
    std::ofstream output_file;
    output_file.setf(std::ios::scientific,std::ios::floatfield);
    output_file.precision(7);

    // Opening file
    std::string file_path = DATA_PATH + "/" + file_name;
    output_file.open(file_path);
    assert(output_file.is_open());

    // Write data
    for (int i=0; i<n; i++){
    output_file << std::setw(15) << x[i]
                << std::setw(15) << y[i] << std::endl;
    }

    output_file.close();

}

double* pointwiseError(double* comp_sol, double* true_sol, int n){
    double* error = new double[n];
    for ( int i=0; i<n; i++ ){
        error[i] = std::abs(comp_sol[i] - true_sol[i]);
    }
    return error;
}

double* perturbValues(double* values, int size){
    double* new_values = new double[size];
    for (int i=0; i<size; i++){
        double perturbation = randomReal(-.005,.005);
        new_values[i] = values[i] + perturbation;
    }
    return new_values;
}

void Q2(){
    int n_nodes = 4;
    // Function to be used in the interpolation.
    double* (*function)(double* xs, int size);
    function = &f;

    // Nodes in [-5,5]
    double* nodes = linspace(-5,5, n_nodes);

    // Values of f at the nodes
    double* values = function(nodes, n_nodes);

    // Instantiate Interpolant
    Interpolant p(nodes, values, n_nodes);

    // Mesh Points
    int mesh_size = 1000;
    double* mesh = linspace(-5,5, mesh_size);
    double* ps = new double[mesh_size];
    p.Evaluate(mesh, mesh_size, ps);

    // Point-wise Error
    double* true_sol = function(mesh, mesh_size);
    double* errors = pointwiseError(ps, true_sol, mesh_size);
    double inf_norm = infinityNorm(errors, mesh_size);

    // Output
    std::cout.precision(5);
    std::cout << "Interpolation error (inf-norm) = ";
    std::cout << std::scientific << inf_norm << std::endl;

    saveData("Q2_at_nodes_4nodes.dat", nodes, values, n_nodes);
    saveData("Q2_at_mesh_points_4nodes.dat", mesh, ps, mesh_size);
    saveData("Q2_errors_4nodes.dat", mesh, errors, mesh_size);
    saveData("Q2_true_sol_4nodes.dat", mesh, true_sol, mesh_size);

    delete[] nodes;
    delete[] values;
    delete[] mesh;
    delete[] ps;
    delete[] true_sol;
    delete[] errors;
}

void testRungePhenom(){

    int n_nodes = 20;
    // Function to be used in the interpolation.
    double* (*function)(double* xs, int size);
    function = &runge_f;

    // Nodes in [-5,5]
    double* nodes = linspace(-5,5, n_nodes);

    // Values of f at the nodes
    double* values = function(nodes, n_nodes);

    // Instantiate Interpolant
    Interpolant p(nodes, values, n_nodes);

    // Mesh Points
    int mesh_size = 1000;
    double* mesh = linspace(-5,5, mesh_size);
    double* ps = new double[mesh_size];
    p.Evaluate(mesh, mesh_size, ps);

    // Point-wise Error
    double* true_sol = function(mesh, mesh_size);
    double* errors = pointwiseError(ps, true_sol, mesh_size);
    double inf_norm = infinityNorm(errors, mesh_size);

    // Output
    std::cout.precision(5);
    std::cout << "Interpolation error (inf-norm) = ";
    std::cout << std::scientific << inf_norm << std::endl;

    saveData("Q3_at_nodes_20nodes.dat", nodes, values, n_nodes);
    saveData("Q3_at_mesh_points_20nodes.dat", mesh, ps, mesh_size);
    saveData("Q3_errors_20nodes.dat", mesh, errors, mesh_size);
    saveData("Q3_true_sol_20nodes.dat", mesh, true_sol, mesh_size);

    delete[] nodes;
    delete[] values;
    delete[] mesh;
    delete[] ps;
    delete[] true_sol;
    delete[] errors;
}

void perturbationAnalysis(){
    int n_nodes = 30;
    int mesh_size = 1000;
    // Function to be used in the interpolation.
    double* (*function)(double* xs, int size);
    function = &sin_f;

    // Nodes in [-1,1]
    double* nodes = linspace(-1,1, n_nodes);

    // Mesh in [-1,1]
    // (to evaluate the true solution and the interpolant)
    double* mesh = linspace(-1,1, mesh_size);

    // Values of f at the nodes
    double* values = function(nodes, n_nodes);

    // Perturbated Values of f at the nodes
    double* perturb_vals = perturbValues(values, n_nodes);

    // Instantiate Interpolant
    Interpolant p(nodes, values, n_nodes);
    double* ps = new double[mesh_size];
    p.Evaluate(mesh, mesh_size, ps);

    // Instantiate Perturbated Interpolant
    Interpolant p_perturb(nodes, perturb_vals, n_nodes);
    double* ps_perturb = new double[mesh_size];
    p_perturb.Evaluate(mesh, mesh_size, ps_perturb);

    // Point-wise Errors
    double* values_errors = pointwiseError(values, perturb_vals, mesh_size);
    double val_errors_norm = infinityNorm(values_errors, mesh_size);
    double* interpolation_errors = pointwiseError(ps, ps_perturb, mesh_size);
    double interp_errors_norm = infinityNorm(interpolation_errors, mesh_size);

    // Output
    std::cout.precision(5);
    std::cout << "Max discrepancy in f = ";
    std::cout << std::scientific << val_errors_norm << std::endl;
    std::cout << "Max discrepancy in p = ";
    std::cout << std::scientific << interp_errors_norm << std::endl;

    // Save files
    saveData("Q4_data_30nodes.dat",nodes,values,n_nodes);
    saveData("Q4_perturbed_data_30nodes.dat",nodes,perturb_vals,n_nodes);
    saveData("Q4_interpolated_data_30nodes.dat",mesh,ps,mesh_size);
    saveData("Q4_perturbed_interpolated_data_30nodes.dat",mesh,ps_perturb,mesh_size);

    delete[] nodes;
    delete[] mesh;
    delete[] values;
    delete[] perturb_vals;
    delete[] ps;
    delete[] ps_perturb;
    delete[] values_errors;
    delete[] interpolation_errors;
}

void chebyshevInterpolation(){
    int n_nodes = 22;
    // Function to be used in the interpolation.
    double* (*function)(double* xs, int size);
    function = &runge_f;

    // Nodes in [-5,5]
    double* nodes = chebyshevNodes(-5,5, n_nodes);

    // Values of f at the nodes
    double* values = function(nodes, n_nodes+1);

    // Instantiate Interpolant
    Interpolant p(nodes, values, n_nodes+1);

    // Mesh Points
    int mesh_size = 1000;
    double* mesh = linspace(-5,5, mesh_size);
    double* ps = new double[mesh_size];
    p.Evaluate(mesh, mesh_size, ps);

    // Point-wise Error
    double* true_sol = function(mesh, mesh_size);
    double* errors = pointwiseError(ps, true_sol, mesh_size);
    double inf_norm = infinityNorm(errors, mesh_size);

    // Output
    std::cout.precision(5);
    std::cout << "Interpolation error (inf-norm) = ";
    std::cout << std::scientific << inf_norm << std::endl;

    saveData("Q5_at_nodes_22nodes.dat", nodes, values, n_nodes+1);
    saveData("Q5_at_mesh_points_22nodes.dat", mesh, ps, mesh_size);
    saveData("Q5_errors_22nodes.dat", mesh, errors, mesh_size);
    saveData("Q5_true_sol_22nodes.dat", mesh, true_sol, mesh_size);

    delete[] nodes;
    delete[] values;
    delete[] mesh;
    delete[] ps;
    delete[] true_sol;
    delete[] errors;
}
