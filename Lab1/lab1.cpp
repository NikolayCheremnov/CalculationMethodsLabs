#include "lab1.h"


Lab1::Lab1():
    ENABLE_LOGGING{false},
    logger {new StreamLogger(nullptr)},
    A {nullptr},
    b{nullptr}
{

}

Lab1::Lab1(bool enableLogging, ostream *stream) : Lab1()
{
    if (ENABLE_LOGGING = enableLogging) {
        logger = new StreamLogger(&clog);
    } else
        logger = new StreamLogger(nullptr);
}

Lab1::~Lab1()
{
    if (A != nullptr)
        delete A;
    if (b != nullptr)
        delete b;
    if (logger != nullptr)
        delete logger;
}

void Lab1::setSourceData(double **_A, double *_b, int n)
{
    A = new SquareMatrix<double>(n, 0);
    b = new Vector<double>(n, 0);
    for (int i = 0; i < n; i++) {
        b->set(i, _b[i]);
        for (int j = 0; j < n; j++)
           A->set(i, j, _A[i][j]);
    }

    logger->log("Setting source data for Lab 1 ...");
    logger->log("A = \n" + A->get_data_str());
    logger->log("b = " + b->get_data_str());
}

tuple<TriangularMatrix<double> *, TriangularMatrix<double> *> Lab1::CalculateLUMatrices()
{
    // L and U matrices
    TriangularMatrix<double>* L = new TriangularMatrix<double>(A->get_size(), 1, false);
    TriangularMatrix<double>* U = new TriangularMatrix<double>(A->get_size(), 0, true);

    logger->log("Finding L and U matrices");

    for (int i = 0; i < A->get_size(); i++)
        for (int j = 0; j < A->get_size(); j++) {
            double sum = 0;
            if (i <= j) { // find Uij
                for (int k = 0; k < i; k++)
                    sum += L->get(i, k) * U->get(k, j);
                U->set(i, j, A->get(i, j) - sum);
            } else { // find Lij
                for (int k = 0; k < j; k++)
                    sum += L->get(i, k) * U->get(k, j);
                L->set(i, j, (A->get(i, j) - sum) / U->get(j, j));
            }
        }

    logger->log("L = \n" + L->get_data_str());
    logger->log("U = \n" + U->get_data_str());
    return tuple<TriangularMatrix<double> *, TriangularMatrix<double> *>(L, U);
}

void Lab1::TestSimpleLU()
{

//    double** A = new double*[4];
//    for (int i = 0; i < 4; i++)
//        A[i] = new double[4];
//    A[0][0] = 5; A[0][1] = 7; A[0][2] = 6; A[0][3] = 5;
//    A[1][0] = 7; A[1][1] = 10; A[1][2] = 8; A[1][3] = 7;
//    A[2][0] = 6; A[2][1] = 8; A[2][2] = 10; A[2][3] = 9;
//    A[3][0] = 5; A[3][1] = 7; A[3][2] = 9; A[3][3] = 10;

//    double b[4] = {23, 32, 33, 31};

    double** A = new double*[3];
    for (int i = 0; i < 3; i++)
        A[i] = new double[3];
    A[0][0] = 2; A[0][1] = -1; A[0][2] = 1;
    A[1][0] = 4; A[1][1] = 3; A[1][2] = 1;
    A[2][0] = 6; A[2][1] = -13; A[2][2] = 6;

    double b[3] = {23, 32, 33};

    setSourceData(A, (double*) b, 3);
    CalculateLUMatrices();
}
