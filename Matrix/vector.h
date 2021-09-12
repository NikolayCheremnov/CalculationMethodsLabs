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


    // getters
    int get_size() { return this->m; }

    // setters
    void set(int index, T value){
        if (index >= this->n)
            throw; // TODO: correct exceptions!
        this->data[0][index] = value;
    }

};

#endif // VECTOR_H
