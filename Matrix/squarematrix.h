#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "basematrix.h"
#include "vector.h"

template <class T>
class SquareMatrix : public BaseMatrix<T>
{
protected:
    SquareMatrix() {}

public:
    SquareMatrix(int n, T defaultValue) : BaseMatrix<T> (n, n, defaultValue) {}

    // getters
    virtual int get_size() { return this->n; }
    virtual T get(int i, int j){
        if (i >= this->m || j >= this->n)
            throw;  // TODO: exceptions
        return this->data[i][j];
    }

    // setters
    virtual void set(int i, int j, T value){
        if (i >= this->m || j >= this->n || i < 0 || j < 0)
            throw;  // TODO: exceptions
        this->data[i][j] = value;
    }

    // arithmetic operations with matrices

    // multiply by vector ptr
    Vector<T>* operator*(Vector<T>* vector) {
        Vector<T>* transposed = (Vector<T>*)vector->clone();
        transposed->Transpose();
        BaseMatrix<T>* result = this->MultiplyByMatrix(transposed);
        delete transposed;
        Vector<T>* result_v = new Vector<T>(result->get_m(), 0);
        for (int i = 0; i < result_v->get_size(); i++)
            result_v->set(i, result->get(i, 0));
        delete result;
        return result_v;
    }
};

#endif // SQUAREMATRIX_H
