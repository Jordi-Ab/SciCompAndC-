#include <iostream>

#include "ForwardEulerSolver.hpp"


ForwardEulerSolver::ForwardEulerSolver (ODEInterface& anODESystem,
        const Vector& initialState,
        const double initialTime,
        const double finalTime,
        const double stepSize,
        const std::string outputFileName,
        const int saveGap,
        const int printGap)
        {
            // Initialise protected variables inherited from AbstractODESolver
            mpODESystem = &anODESystem;
            mInitialTime = initialTime;
            mFinalTime = finalTime;
            mStepSize = stepSize;

            // Initialise variables in ForwardEulerSolver
            mpInitialState = new Vector(initialState);
            mOutputFileName = outputFileName;
            mSaveGap = saveGap;
            mPrintGap = printGap;

        }


ForwardEulerSolver::~ForwardEulerSolver()
{
    delete mpInitialState;
}

void ForwardEulerSolver::Solve()
{
    Vector* f = new Vector(1);
    Vector* u = new Vector(*mpInitialState);

    double time = mInitialTime;

    for(int i=1; i<(mFinalTime-mInitialTime)/mStepSize; i++)
    {
        mpODESystem->ComputeF(time,*u,*f);

        u[i] = u[i-1] + f[0]*mStepSize;
        time += mStepSize;
    }

    std::cout << u << std::endl;




    delete f;
    delete u;
}
