#ifndef FORWARDEULERSOLVERHEADERDEF
#define FORWARDEULERSOLVERHEADERDEF

#include "ODEInterface.hpp"
#include "AbstractODESolver.hpp"
#include "Vector.hpp"
#include "LinearODE.hpp"

class ForwardEulerSolver: public AbstractODESolver
{

public:
    // Specialised Constructor
    ForwardEulerSolver (ODEInterface& anODESystem,
        const Vector& initialState,
        const double initialTime,
        const double finalTime,
        const double stepSize,
        const std::string outputFileName = "output.dat",
        const int saveGap = 1,

        const int printGap = 1);

    // Destructor
    ~ForwardEulerSolver();

    // Solve
    void Solve();

private:

    // Default Constructor
    ForwardEulerSolver();

    // Variables
    Vector* mpInitialState;
    std::string mOutputFileName;
    int mSaveGap;
    int mPrintGap;

};


#endif
