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
            throw; // TODO: correct exceptions!
        return this->data[0][index];
    }

    // setters
    virtual void set(int index, T value){
        if (index >= this->n)
            throw; // TODO: correct exceptions!
        this->data[0][index] = value;
    }

    // actions with vector



};

#endif // VECTOR_H
