HEADERS += \
    LinearSystem.hpp \
    Vector.hpp \
    Matrix.hpp \
    AbstractIterativeLinearSolver.hpp \
    JacobiSolver.hpp \
    SORSolver.hpp \
    GaussSeidelSolver.hpp \
    DampedJacobiSolver.hpp \
    ConvergenceCriterion.hpp

SOURCES += \
    LinearSystem.cpp \
    Vector.cpp \
    Matrix.cpp \
    driver.cpp \
    DampedJacobiSolver.cpp \
    GaussSeidelSolver.cpp \
    JacobiSolver.cpp \
    SORSolver.cpp \
    AbstractIterativeLinearSolver.cpp \
    ConvergenceCriterion.cpp
