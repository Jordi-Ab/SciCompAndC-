#ifndef INTERPOLANT_HPP
#define INTERPOLANT_HPP


class Interpolant{

public:
    Interpolant(const double* nodes, const double* values, const int n_nodes);
    void Evaluate(const double* xi, int n_points, double* p) const;

private:

    //INSTANCE VARIABLES:
    const double* nodes;
    const double* values;
    int degree;

    //CONSTRUCTORS:
    Interpolant();


    //FUNCTIONS:

    void evaluatePn(int point, double x, double* pns) const;
    double evaluateL(int index, double x) const;

};

#endif // INTERPOLANT_HPP
