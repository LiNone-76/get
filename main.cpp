#include <iostream>
#include "CbcModel.hpp"
#include "ZteModel.h"
int main() {
    OsiClpSolverInterface solver;
    int numMpsReadErrors = solver.readMps("D:/zet/mpsdata/haprp.mps");
    assert(numMpsReadErrors == 0);

//    ZteModel model(solver);

    CbcModel model(solver);

    model.branchAndBound();

    int numberColumns = model.solver()->getNumCols();
    const double *solution = model.bestSolution();
    for (int iColumn = 0; iColumn < numberColumns; iColumn++) {
        double value = solution[iColumn];
        if (fabs(value) > 1.0e-7 && model.solver()->isInteger(iColumn)) {
            printf("%d has value"
                   " %g\n", iColumn, value);
        }
        return 0;
    }

}
