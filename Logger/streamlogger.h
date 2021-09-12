#ifndef STREAMLOGGER_H
#define STREAMLOGGER_H

#include "ilogger.h"

#include <iostream>
#include <fstream>

using namespace std;

class StreamLogger : public ILogger
{
private:
    ostream* out;

public:
    StreamLogger(): out {nullptr} {};
    StreamLogger(ostream* stream) : out {stream} {};
    ~StreamLogger() {};

    virtual void log(string msg);
};

#endif // STREAMLOGGER_H
