#include "lab1.h"


Lab1::Lab1():
    ENABLE_LOGGING{false},
    logger {new PlugLogger()},
    A {nullptr},
    b{nullptr}
{

}

Lab1::Lab1(bool enableLogging, ILogger* logger) : Lab1()
{
    if (ENABLE_LOGGING = enableLogging)
        this->logger = logger;
    else
        logger = new PlugLogger();
}

Lab1::~Lab1()
{
    if (A != nullptr)
        delete A;
    if (b != nullptr)
        delete b;
    if (!ENABLE_LOGGING)
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
                if (U->get(j, j) == 0) {
                    logger->log("matrix U is degenerate");
                    delete L;
                    delete U;
                    return tuple<TriangularMatrix<double> *, TriangularMatrix<double> *> (nullptr, nullptr);
                }
                L->set(i, j, (A->get(i, j) - sum) / U->get(j, j));
            }
        }

    logger->log("L = \n" + L->get_data_str());
    logger->log("U = \n" + U->get_data_str());
    return tuple<TriangularMatrix<double> *, TriangularMatrix<double> *>(L, U);
}

Vector<double>* Lab1::CalculateY(TriangularMatrix<double>* L)
{
    Vector<double>* y = new Vector<double>(A->get_size(), 0);

    logger->log("Finding y vector");

    for (int i = 0; i < A->get_size(); i++) {
        double yi = b->get(i);
        for (int j = 0; j < i; j++)
            yi -= L->get(i, j) * y->get(j);
        y->set(i, yi);
    }

    logger->log("y = " + y->get_data_str());
    return y;
}

Vector<double> *Lab1::CalculateX(TriangularMatrix<double> *U, Vector<double> *y)
{
    Vector<double>* x = new Vector<double>(A->get_size(), 0);

    logger->log("Finding x vector");

    for (int i = A->get_size() - 1; i >= 0; i--) {
        double xi = y->get(i);
        for (int j = i + 1; j < A->get_size(); j++)
            xi -= U->get(i, j) * x->get(j);
        if (U->get(i, i) == 0) {
            logger->log("matrix U is degenerate");
            delete x;
            return nullptr;
        }
        x->set(i, xi / U->get(i, i));
    }

    logger->log("x = " + x->get_data_str());
    return x;
}

double Lab1::CalculateDet(TriangularMatrix<double> *U)
{
    double det = 1;
    for (int i = 0; i < U->get_size(); i++)
        det *= U->get(i, i);

    logger->log("det = " + to_string(det));
    return det;
}

SquareMatrix<double> *Lab1::CalculateInverseMatrix(TriangularMatrix<double> *L, TriangularMatrix<double> *U)
{
    SquareMatrix<double>* X = new SquareMatrix<double>(this->A->get_size(), 0);

    for (int i = this->A->get_size() - 1; i >= 0; i--)
        for (int j = this->A->get_size() - 1; j >= 0; j--) {
            double Xij = 0;
            if (i == j) {
                Xij = 1;
                for (int k = j + 1; k < this->A->get_size(); k++)
                    Xij -= U->get(j, k) * X->get(k, j);
                if (U->get(i, j) == 0) {
                    logger->log("matrix U is degenerate");
                    delete X;
                    return nullptr;
                }
                Xij /= U->get(i, j);
            }
            else if (i < j) {
                for (int k = i + 1; k < this->A->get_size(); k++)
                    Xij += U->get(i, k) * X->get(k, j);
                if (U->get(i, i) == 0) {
                    logger->log("matrix U is degenerate");
                    delete X;
                    return nullptr;
                }
                Xij /= -U->get(i, i);
            } else {
                for (int k = j + 1; k < this->A->get_size(); k++)
                    Xij -= X->get(i, k) * L->get(k, j);
            }
            X->set(i, j, Xij);
        }

    logger->log("A^-1 = \n" + X->get_data_str());
    return X;
}

void Lab1::SimpleTest()
{

//    double** A = new double*[4];
//    for (int i = 0; i < 4; i++)
//        A[i] = new double[4];
//    A[0][0] = 5; A[0][1] = 7; A[0][2] = 6; A[0][3] = 5;
//    A[1][0] = 7; A[1][1] = 10; A[1][2] = 8; A[1][3] = 7;
//    A[2][0] = 6; A[2][1] = 8; A[2][2] = 10; A[2][3] = 9;
//    A[3][0] = 5; A[3][1] = 7; A[3][2] = 9; A[3][3] = 10;

//    double b[4] = {23, 32, 33, 31};
try{
    double** A = new double*[3];
    for (int i = 0; i < 3; i++)
        A[i] = new double[3];
    A[0][0] = 2; A[0][1] = -1; A[0][2] = 1;
    A[1][0] = 4; A[1][1] = 3; A[1][2] = 1;
    A[2][0] = 6; A[2][1] = -13; A[2][2] = 6;

    double b[3] = {23, 32, 33};

    // setting source data
    setSourceData(A, (double*) b, 3);

    // LU-method calculation
    auto tuple_LU = CalculateLUMatrices();
    TriangularMatrix<double>* L = get<0>(tuple_LU);
    TriangularMatrix<double>* U = get<1>(tuple_LU);
    Vector<double>* y = CalculateY(L);
    Vector<double>* x = CalculateX(U, y);

    // inverse matrix and determinant
    SquareMatrix<double>* _A = CalculateInverseMatrix(L, U);
    double detA = CalculateDet(U);

    // discrepancy
    Vector<double>* Ly = ((*L) * y);
    Vector<double>* Ux = ((*U) * x);
    Vector<double>* Ax = (*(this->A) * x);
    Vector<double>* b_d = (*(this->b)) - Ax;
    SquareMatrix<double>* E = new SquareMatrix<double>(this->A->get_n(), 0);
    E->fillMainDiagonal(1);
    SquareMatrix<double>* A_A = (*(this->A)) * _A;
    SquareMatrix<double>* A_E = (*A_A) - E;

    // checking solutions
    logger->log("Ly = b = " + Ly->get_data_str());
    logger->log("Ux = y = " + Ux->get_data_str());
    logger->log("Ax = b = " + Ax->get_data_str());

    // discrepancy
    logger->log("b - Ax = " + b_d->get_data_str());
    logger->log("AA^-1 - E = \n" + A_E->get_data_str());

    // TODO: add memory cleaning here
    delete y;
    delete Ly;
    delete x;
    delete Ux;
    delete Ax;
    delete L;
    delete U;
    delete _A;
    for (int i = 0; i < 3; i++)
        delete []A[i];
    delete []A;
    delete E;
    delete A_A;
    delete b_d;
    delete A_E;
    }
    catch (exception& ex) {
        logger->log(ex.what());
    }
}

void Lab1::TestWithData(double **A, double *b, int n)
{
    // pointers
    TriangularMatrix<double>* L = nullptr;
    TriangularMatrix<double>* U = nullptr;
    Vector<double>* y = nullptr;
    Vector<double>* x = nullptr;
    SquareMatrix<double>* _A = nullptr;
    Vector<double>* Ax = nullptr;
    Vector<double>* b_d = nullptr;
    SquareMatrix<double>* E = nullptr;
    SquareMatrix<double>* A_A = nullptr;
    SquareMatrix<double>* A_E = nullptr;

    auto release_memory = [=]() {
        if (L != nullptr) delete L;
        if (U != nullptr) delete U;
        if (y != nullptr) delete y;
        if (x != nullptr) delete x;
        if (_A != nullptr) delete _A;
        if (Ax != nullptr) delete Ax;
        if (b_d != nullptr) delete b_d;
        if (E != nullptr) delete E;
        if (A_A != nullptr) delete A_A;
        if (A_E != nullptr) delete A_E;
    };

    try {
        // setting source data
        setSourceData(A, b, n);

        // LU-method calculation
        auto tuple_LU = CalculateLUMatrices();
        L = get<0>(tuple_LU);
        U = get<1>(tuple_LU);
        if (L == nullptr || U == nullptr)
            throw exception();
        y = CalculateY(L);
        x = CalculateX(U, y);
        if (x == nullptr)
            throw exception();

        // inverse matrix and determinant
        _A = CalculateInverseMatrix(L, U);
        if (_A == nullptr)
            throw _A;

        CalculateDet(U);


        // discrepancy
        Ax = (*(this->A) * x);
        b_d = (*(this->b)) - Ax;
        logger->log("b - Ax = " + b_d->get_data_str());
        E = new SquareMatrix<double>(this->A->get_n(), 0);
        E->fillMainDiagonal(1);
        A_A = (*(this->A)) * _A;
        A_E = (*A_A) - E;
        logger->log("AA^-1 - E = \n" + A_E->get_data_str());
        logger->log("||A|| = " + to_string(this->A->MaxOfAbs()));
        logger->log("||A^-1|| = " + to_string(_A->MaxOfAbs()));
        logger->log("||A|| * ||A^-1|| = " + to_string(this->A->MaxOfAbs() * _A->MaxOfAbs()));
    }
    catch (exception& ex) {
        release_memory();
        logger->log(ex.what());
        return;
    }
    logger->log("test with data successful completed");
    release_memory();
}
