#ifndef TRIANGULARMATRIX_H
#define TRIANGULARMATRIX_H

#include "squarematrix.h"

template <class T>
class TriangularMatrix : public SquareMatrix<T>
{
private:
    bool isUpperOne;

public:
    TriangularMatrix(int n, T defaultValue, bool isUpperOne){
        this->isUpperOne = isUpperOne;
        this->data = new T*[n];
        for (int i = 0; i < n; i++) {
            this->data[i] = new T[i + 1];
            for (int j = 0; j <= i; j++) {
                this->data[i][j] = defaultValue;
            }
        }
        this->n = this->m = n;
    }

    // getters
    virtual T get(int i, int j){
        if (i >= this->n || j >= this->n)
            throw; // TODO: exceptions!!!
        if (isUpperOne) {
            if (i > j)
                throw; // TODO: exceptions
            return this->data[j][i];
        } else {
            if (j > i)
                throw; // TODO: exceptions
            return this->data[i][j];
        }
    }

    virtual std::string get_data_str(){
        std::stringstream as_str;
        for (int i = 0; i < this->m; i++) {
            for (int j = 0; j < this->n; j++) {
                if (!isUpperOne)
                    if (j <= i)
                        as_str << this->data[i][j] << " ";
                    else
                        as_str << 0 << " ";
                else
                    if (i <= j)
                        as_str << this->data[j][i] << " ";
                    else
                        as_str << 0 << " ";
            }
            as_str << std::endl;
        }
        return as_str.str();
    }


    // setters
    virtual void set(int i, int j, T value){
        if (i >= this->n || j >= this->n)
            throw; // TODO: exceptions!!!
        if (isUpperOne) {
            if (i > j)
                throw; // TODO: exceptions
            this->data[j][i] = value;
        } else {
            if (j > i)
                throw; // TODO: exceptions
            this->data[i][j] = value;
        }
    }

};

#endif // TRIANGULARMATRIX_H