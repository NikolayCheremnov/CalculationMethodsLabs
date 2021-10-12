#include "lab2.h"

void Lab2::clear_data()
{
    n = nrhs = lda=  ldb = info = 0;
    if (a != nullptr)
        delete a;
    if (b != nullptr)
        delete b;
    if (ipiv != nullptr)
        delete ipiv;

    state = UNINITIALIZED;
}

Lab2::Lab2() : Lab2(false, nullptr)
{

}

Lab2::Lab2(bool enableLogging, ILogger *logger) :
    state{UNINITIALIZED}, n{0}, nrhs{0}, lda{0}, a{nullptr}, ldb{0}, b{nullptr}, ipiv{nullptr}, info{0}
{
    if (ENABLE_LOGGING = enableLogging)
        this->logger = logger;
    else
        logger = new PlugLogger();
}

Lab2::~Lab2()
{
    clear_data();
}

void Lab2::set_simple_source_data(int N, double **reA, double **imA, double *reB, double *imB)
{
    if (state == INITIALIZED || state == SOLVED)
        clear_data();

    // sizes
    n = lda = N;
    nrhs = ldb = 1;

    // memory allocation
    ipiv = new lapack_int[n];
    a = new lapack_complex_double[n * n];
    b = new lapack_complex_double[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            a[i*lda + j] = lapack_make_complex_double(reA[i][j], imA[i][j]);
        b[i] = lapack_make_complex_double(reB[i], imB[i]);
    }

    logger->log("Source data setted: ");
    log_matrix("Entry matrix A", n, n, a, lda);
    log_matrix("Entry right side b", n, nrhs, b, ldb);

    state = INITIALIZED;
}

void Lab2::solve_system()
{
    if (state != INITIALIZED) {
        logger->log("Can`t solve UNITIALIZED system");
        return;
    }
    info = LAPACKE_zgesv(LAPACK_ROW_MAJOR, n, nrhs, a, lda, ipiv, b, ldb);
    if (info > 0) {
        logger->log("The diagonal element of the triangular factor of A,\n");
        logger->log("U(" +  to_string(info) + ", " + to_string(info) + ") is zero, so that A is singular;\n");
        logger->log("the solution could not be computed.\n");
    }
    else
        log_matrix("Solution: ", n, nrhs, b, ldb);
    state = SOLVED;
}

void Lab2::simple_test_zgesv()
{
    const int N = 2;
    double** reA = new double*[N];
    reA[0] = new double[N];
    reA[0][0] = reA[0][1] = 1;
    reA[1] = new double[N];
    reA[1][0] = reA[1][1] = 1;
    double** imA = new double*[N];
    imA[0] = new double[N];
    imA[0][0] = 1; imA[0][1] = -1;
    imA[1] = new double[N];
    imA[1][0] = 2; imA[1][1] = -2;
    double* reB = new double[N];
    reB[0] = -1; reB[1] = -4;
    double* imB = new double[N];
    imB[0] = 1; imB[1] = 1;
    set_simple_source_data(N, reA, imA, reB, imB);
    solve_system();
}

void Lab2::log_matrix( char* desc, lapack_int m, lapack_int n, lapack_complex_double* matrix, lapack_int lda ) {
    lapack_int i, j;
    string out = string("\n") + desc + "\n";
     for( i = 0; i < m; i++ ) {
            for( j = 0; j < n; j++ )
                out += string("(") +
                            to_string(lapack_complex_double_real(matrix[i*lda + j])) + ", " +
                            to_string(lapack_complex_double_imag(matrix[i*lda + j])) +
                            ") ";
            out += "\n";
    }
    logger->log(out);
}

/* Auxiliary routine: printing a vector of integers */
void Lab2::print_int_vector( char* desc, lapack_int n, lapack_int* a ) {
        lapack_int j;
        printf( "\n %s\n", desc );
        for( j = 0; j < n; j++ ) printf( " %6i", a[j] );
        printf( "\n" );
}
