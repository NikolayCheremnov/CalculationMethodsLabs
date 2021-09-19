#include "stringlogger.h"

StringLogger::StringLogger()
{
    data = "";
}

void StringLogger::log(string msg)
{
    data += msg + "\n";
}
