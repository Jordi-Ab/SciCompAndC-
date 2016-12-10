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

    void evaluatePn(int point, double x, double* pns) const;
    void evaluateLagrange(int point, double x, double* pns) const;
    double getLj(int index, double x) const;
    void computeWeights();
    void computeWeightsAnalytically();
    void computeWeightsIterativeley();

};

#endif // INTERPOLANT_HPP
