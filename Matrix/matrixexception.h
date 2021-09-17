#ifndef MATRIXEXCEPTION_H
#define MATRIXEXCEPTION_H

#include <exception>
#include <iostream>

using namespace std;

class MatrixException : public exception
{
private:
    string msg;

public:
    MatrixException(string msg) : msg{msg} {}
    virtual const char* what() { return msg.c_str(); }
};

#endif // MATRIXEXCEPTION_H
