#ifndef LAB1_H
#define LAB1_H

#include <tuple>

#include <Matrix/squarematrix.h>
#include <Matrix/triangularmatrix.h>
#include <Matrix/vector.h>
#include <Logger/ilogger.h>
#include <Logger/pluglogger.h>

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
    Lab1(bool enableLogging, ILogger* external_logger);
    ~Lab1();

    // setting sources data
    void setSourceData(double** _A, double* _b, int n);

    // LU-algorithm methods
    tuple<TriangularMatrix<double>*, TriangularMatrix<double>*> CalculateLUMatrices();
    Vector<double>* CalculateY(TriangularMatrix<double>* L);
    Vector<double>* CalculateX(TriangularMatrix<double>* U, Vector<double>* y);
    double CalculateDet(TriangularMatrix<double>* U);
    SquareMatrix<double>* CalculateInverseMatrix(TriangularMatrix<double>* L, TriangularMatrix<double>* U);
    // Tests
    void SimpleTest();
    void TestWithData(double** A, double* b, int n);
};

#endif // LAB1_H
