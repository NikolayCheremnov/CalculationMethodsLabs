#ifndef BASEMATRIX_H
#define BASEMATRIX_H

#include <iostream>
#include <sstream>
#include <string>


template <class T>
class BaseMatrix
{
protected:
    T** data; // matrix data
    int m, n; // matrix dimension

protected:
    // protected constructors
    BaseMatrix() {}

private:
    void clear_data() {
        if (data != nullptr)
            for (int i = 0; i < m; i++)
                if (data[i] != nullptr)
                    delete []data[i];
        delete []data;
    }

public:
    BaseMatrix(int m, int n, T defaultValue){
        data = new T*[m];
        for (int i = 0; i < m; i++) {
            data[i] = new T[n];
            for (int j = 0; j < n; j++)
                data[i][j] = defaultValue;
        }
        this->m = m;
        this->n = n;
    }
    virtual ~BaseMatrix(){
        clear_data();
    }

    // prototype
    virtual BaseMatrix<T>* clone() {
        BaseMatrix<T>* copy = new BaseMatrix<T>(m, n, 0);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                copy->data[i][j] = data[i][j];
        return copy;
    }

    // getters
    int get_m() { return m; }
    int get_n() { return n; }
    virtual int get_size() {
        throw std::exception(); // TODO: create own exception here
        return 0;
    }
    virtual std::string get_data_str(){
        std::stringstream as_str;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                as_str << this->data[i][j] << " ";
            if (i != m - 1)
                as_str << std::endl;
        }
        return as_str.str();
    }

    virtual T get(int i, int j) {
        if (i >= m || j >= n || i < 0 || j < 0)
            throw std::exception(); // TODO: create own exception here
        return data[i][j];
    }

    // setters
    virtual void set(int i, int j, T value) {
        if (i >= m || j >= n || i < 0 || j < 0)
            throw std::exception(); // TODO: create own exception here
        data[i][j] = value;
    }

    // arithmetic operations with matrices
    BaseMatrix<T>* MultiplyByMatrix(BaseMatrix<T>* matrix) {
        if (n != matrix->m)
            throw std::exception(); // TODO: create own exception here

        BaseMatrix<T>* result = new BaseMatrix<T>(m, matrix->n, 0);

        for (int i = 0; i < m; i++)
            for (int j = 0; j < matrix->n; j++) {
                T elem = 0;
                for (int k = 0; k < n; k++)
                    elem += data[i][k] * matrix->data[k][j];
                result->set(i, j, elem);
            }
        return result;
    }

    BaseMatrix<T>* SubstructionByMatrix(BaseMatrix<T>* matrix) {
        if (n != matrix->get_n() || m != matrix->get_m())
            throw std::exception(); // TODO: create own exception here

        BaseMatrix<T>* result = new BaseMatrix<T>(m, n, 0);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                result->set(i, j, data[i][j] - matrix->data[i][j]);

        return result;
    }

    // actions current with matrix
    void Transpose() {
        T** new_data = new T*[n];
        for (int i = 0; i < n; i++)
            new_data[i] = new T[m];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                new_data[j][i] = data[i][j];

        clear_data();
        data = new_data;

        int tmp = n;
        n = m;
        m = tmp;
    }

};

#endif // BASEMATRIX_H
