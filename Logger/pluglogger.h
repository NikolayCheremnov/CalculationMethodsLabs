#ifndef PLUGLOGGER_H
#define PLUGLOGGER_H

#include "ilogger.h"

class PlugLogger : public ILogger
{
public:
    PlugLogger();
    ~PlugLogger() {}

    virtual void log(string msg) {};
};

#endif // PLUGLOGGER_H
