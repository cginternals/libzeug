#include <iostream>
#include <scriptzeug/ScriptEnvironment.h>


using namespace scriptzeug;


int main(int argc, char const *argv[])
{
    ScriptEnvironment scripting;
    scripting.evaluate("var a=2; a*2;");
    scripting.evaluate("a*3;");

    return 0;
}
