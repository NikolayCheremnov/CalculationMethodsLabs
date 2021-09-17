#ifndef VECTOR_H
#define VECTOR_H

#include "basematrix.h"

template <class T>
class Vector : public BaseMatrix<T>
{
public:
    Vector(int size, T defaultValue): BaseMatrix<T> (1, size, defaultValue)
    {

    }

    // prototype
    virtual BaseMatrix<T>* clone() {
        Vector<T>* copy = new Vector(get_size(), 0);
        for (int i = 0; i < get_size(); i++)
            copy->set(i, get(i));
        return copy;
    }


    // getters
    int get_size() { return this->n; }
    T get(int index) {
        if (index >= this->n || index < 0)
            throw MatrixException("vector index out of range");
        return this->data[0][index];
    }

    // setters
    virtual void set(int index, T value){
        if (index >= this->n)
            throw MatrixException("vector index out of range");
        this->data[0][index] = value;
    }

    // actions with vector
    Vector<T>* operator-(Vector<T>* vec) {
        BaseMatrix<T>* sub = this->SubstructionByMatrix(vec);
        Vector<T>* res = ConvertToVector(sub);
        delete sub;
        return res;
    }


    // converters
    static Vector<T>* ConvertToVector(BaseMatrix<T>* dst) {
        if (dst->get_m() != 1)
            throw MatrixException("invalid vector convertation");
        Vector<T>* vec = new Vector<T>(dst->get_n(), 0);
        for (int i = 0; i < dst->get_n(); i++)
            vec->set(i, dst->get(0, i));
        return vec;
    }

};

#endif // VECTOR_H
