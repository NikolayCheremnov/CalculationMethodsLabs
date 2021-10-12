#ifndef LAB2_H
#define LAB2_H

#include  <iostream>

#include <Logger/ilogger.h>
#include <Logger/pluglogger.h>

// lapack headers
#include "lapacke/_lapacke.h"
#include "lapacke/_lapacke_config.h"

enum Lab2ObjectState {
    UNINITIALIZED,
    INITIALIZED,
    SOLVED
};

class Lab2
{
private:
    // logging
    bool ENABLE_LOGGING;
    ILogger* logger;

    // task
    Lab2ObjectState state;

    // source data
    lapack_int n;               // number of equalations
    lapack_int nrhs;            // number of right parts
    lapack_int lda;             // leading dimension of the array A
    lapack_complex_double* a;   // matrix a
    lapack_int ldb;             // leading dimension of the array b
    lapack_complex_double* b;   // vector b;

    // other
    lapack_int* ipiv;
    lapack_int info;

    void clear_data();
    // logs methods
    void log_matrix( char* desc, lapack_int m, lapack_int n, lapack_complex_double* matrix, lapack_int lda );
    void print_int_vector( char* desc, lapack_int n, lapack_int* a );
public:
    // constructors
    Lab2();
    Lab2(bool enableLogging, ILogger* external_logger);
    // desctructor
    ~Lab2();

public:
    void set_simple_source_data(int N, double** reA, double** imA, double* reB, double* imB);
    void solve_system();

    // testing subroutines examples
    void simple_test_zgesv();


};

#endif // LAB2_H
