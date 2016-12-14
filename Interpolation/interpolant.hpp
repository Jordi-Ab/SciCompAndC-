#ifndef INTERPOLANT_HPP
#define INTERPOLANT_HPP


class Interpolant{

public:
    Interpolant(const double* nodes, const double* values, const int n_nodes,
                const bool barycentric_formula = false,
                const bool chebyshev_interpolant=false);

    void Evaluate(const double* xi, int n_points, double* p) const;

private:

    //INSTANCE VARIABLES:
    const double* nodes;
    const double* values;
    int degree;
    const bool barycentric_formula;
    const bool chebyshev_interpolant;
    const double* weights;

    //CONSTRUCTORS:
    Interpolant();


    //FUNCTIONS:

    double evaluateLagrange(const double x) const;
    double evaluateBarycentric(const double x) const;
    double getLj(int index, const double x) const;
    void computeWeights();
    void computeWeightsAnalytically();
    void computeWeightsIterativeley();

};

#endif // INTERPOLANT_HPP
