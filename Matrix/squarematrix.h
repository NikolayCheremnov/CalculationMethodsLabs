#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "basematrix.h"

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
        if (i >= this->m || j >= this->n)
            throw;  // TODO: exceptions
        this->data[i][j] = value;
    }
};

#endif // SQUAREMATRIX_H
