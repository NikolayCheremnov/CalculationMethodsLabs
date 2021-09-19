#ifndef STRINGLOGGER_H
#define STRINGLOGGER_H

#include "ilogger.h"

class StringLogger : public ILogger
{
private:
    string data;
public:
    StringLogger();

    string getLogsStr() { return data; }
    virtual void log(string msg);
};

#endif // STRINGLOGGER_H
