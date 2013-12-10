#include <iostream>
#include <scriptzeug/ScriptEnvironment.h>


using namespace scriptzeug;


int main(int argc, char const *argv[])
{
    ScriptEnvironment scripting;
//    scripting.evaluate("var a=2; a*2;");
//    scripting.evaluate("a*3;");
    scripting.evaluate("test(1, 2, '3', 23.42, 'asd');");

    return 0;
}
