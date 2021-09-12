#ifndef LAB1_H
#define LAB1_H

#include <tuple>

#include <Matrix/squarematrix.h>
#include <Matrix/triangularmatrix.h>
#include <Matrix/vector.h>
#include <Logger/ilogger.h>
#include <Logger/streamlogger.h>

using namespace std;

class Lab1
{
private:
    // logging
    bool ENABLE_LOGGING;
    ILogger* logger;

    SquareMatrix<double>* A;
    Vector<double>* b;

public:
    Lab1();
    Lab1(bool enableLogging, ostream* stream);
    ~Lab1();

    // setting sources data
    void setSourceData(double** _A, double* _b, int n);

    // LU-algorithm methods
    tuple<TriangularMatrix<double>*, TriangularMatrix<double>*> CalculateLUMatrices();

    // Tests
    void TestSimpleLU();
};

#endif // LAB1_H
