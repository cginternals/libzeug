#include <iostream>
#include <scriptzeug/ScriptEnvironment.h>
#include <scriptzeug/Scriptable.h>


using namespace scriptzeug;


void testFunction()
{
    std::cout << "Test function\n";
}


class MyInterface : public Scriptable
{
public:
    MyInterface()
    {
        addFunction("test",                &testFunction);
        addFunction("helloWorld",    this, &MyInterface::helloWorld);
        addFunction("bottlesOfBeer", this, &MyInterface::bottlesOfBeer);
        addFunction("dynamicTest",   this, &MyInterface::dynamicTest);
    }

    ~MyInterface()
    {
    }

    void helloWorld()
    {
        std::cout << "Hello World\n";
    }

    void bottlesOfBeer(int count, float a)
    {
        std::cout << count << " bottles of beer with a propability of " << a << "\%.\n";
    }

    void dynamicTest(const Value &a, const Value &b, const Value &c)
    {
        std::cout << "- a: " << a.toString() << "\n";
        std::cout << "- b: " << b.toString() << "\n";
        std::cout << "- c: " << c.toString() << "\n";
    }
};


int main(int argc, char const *argv[])
{
    MyInterface obj;

    ScriptEnvironment scripting;
    scripting.registerObject("testobj", &obj);
//  scripting.evaluate("testobj.test(1, 2, '3', 23.42, 'asd');");
    scripting.evaluate("testobj.helloWorld();");
    scripting.evaluate("testobj.test();");
    scripting.evaluate("testobj.bottlesOfBeer(120, 3.5, 10);");
    scripting.evaluate("testobj.bottlesOfBeer();");
    scripting.evaluate("testobj.dynamicTest([3.5, {a: 100, b: 200}, 12], \"asd\");");

    return 0;
}
