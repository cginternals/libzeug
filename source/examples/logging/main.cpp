#include <loggingzeug/logging.h>


using namespace loggingzeug;


int main(int argc, char const *argv[])
{
    info() << "Info";
    debug() << "Debug";
    warning() << "Warning";
    critical() << "Critical";
    fatal() << "Fatal";
    
    return 0;
}
