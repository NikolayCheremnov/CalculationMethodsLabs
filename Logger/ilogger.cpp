#include "ilogger.h"

string ILogger::get_current_time_str()
{
    time_t now = time(0);
    struct tm  tstruct;
    char* buf = new char[80];
    tstruct = *localtime(&now);
    strftime(buf, 80, "%Y-%m-%d.%X", &tstruct);
    string res = string(buf);
    delete []buf;
    return res;
}

ILogger::ILogger()
{

}
