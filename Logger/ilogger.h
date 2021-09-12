#ifndef ILOGGER_H
#define ILOGGER_H

#include <iostream>
#include <ctime>

using namespace std;

class ILogger
{
protected:
    string get_current_time_str();

public:
    ILogger();
    virtual ~ILogger() {};

    virtual void log(string msg) = 0;
};

#endif // ILOGGER_H
