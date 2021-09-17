#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "basematrix.h"
#include "vector.h"
#include "matrixexception.h"

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
            throw MatrixException("square matrix index out of range");
        return this->data[i][j];
    }

    // setters
    virtual void set(int i, int j, T value){
        if (i >= this->m || j >= this->n || i < 0 || j < 0)
            throw MatrixException("square matrix index out of range");
        this->data[i][j] = value;
    }

    void fillMainDiagonal(T val) {
        for (int i = 0; i < this->n; i++)
            this->data[i][i] = val;
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

    // multiply by square matrix
    SquareMatrix<T>* operator*(SquareMatrix<T>* mat) {
        BaseMatrix<T>* mul = this->MultiplyByMatrix(mat);
        SquareMatrix<T>* res = ConvertToSquareMatrix(mul);
        delete mul;
        return res;
    }

    SquareMatrix<T>* operator-(SquareMatrix<T>* mat) {
        BaseMatrix<T>* sub = this->SubstructionByMatrix(mat);
        SquareMatrix<T>* res = ConvertToSquareMatrix(sub);
        delete sub;
        return res;
    }

    // static methods

    static SquareMatrix<T>* ConvertToSquareMatrix(BaseMatrix<T>* dst) {
        if (dst->get_n() != dst->get_m())
            throw MatrixException("invalid square matrix convertation");
        SquareMatrix<T>* mat = new SquareMatrix<T>(dst->get_n(), 0);
        for (int i = 0; i < dst->get_n(); i++)
            for (int j = 0; j < dst->get_n(); j++)
                mat->set(i, j, dst->get(i, j));
        return mat;
    }
};

#endif // SQUAREMATRIX_H
