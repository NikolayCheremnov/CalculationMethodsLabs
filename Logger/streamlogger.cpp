#include "streamlogger.h"

void StreamLogger::log(string msg)
{
    if (out == nullptr)
        return;
    (*out) << get_current_time_str() << ": " << msg << endl;
}
