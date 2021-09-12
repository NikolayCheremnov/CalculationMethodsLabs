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
        if (data != nullptr)
            for (int i = 0; i < m; i++)
                if (data[i] != nullptr)
                    delete []data[i];
        delete []data;
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
            as_str << std::endl;
        }
        return as_str.str();
    }


};

#endif // BASEMATRIX_H
