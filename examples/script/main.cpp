#include <iostream>
#include <scriptzeug/ScriptEnvironment.h>
#include <scriptzeug/Scriptable.h>


using namespace scriptzeug;


void testFunction(std::string a)
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

    void dynamicTest(const std::vector<Value> &args)
    {
        std::cout << "Number of arguments: " << args.size() << "\n";

        int i=0;
        for (std::vector<Value>::const_iterator it = args.begin(); it != args.end(); ++it) {
            std::cout << "- " << i << ": " << (*it).toString() << "\n";
            i++;
        }
    }
};


int main(int argc, char const *argv[])
{
    MyInterface obj;

    ScriptEnvironment scripting;
    scripting.registerObject("testobj", &obj);

    Value value;
//  scripting.evaluate("testobj.test(1, 2, '3', 23.42, 'asd');");
    value = scripting.evaluate("1 + 2");
    std::cout << "--> " << value.toString() << "\n";
    value = scripting.evaluate("testobj.helloWorld();");
    std::cout << "--> " << value.toString() << "\n";
    value = scripting.evaluate("testobj.test();");
    std::cout << "--> " << value.toString() << "\n";
    value = scripting.evaluate("testobj.bottlesOfBeer(120, 3.5, 10);");
    std::cout << "--> " << value.toString() << "\n";
    value = scripting.evaluate("testobj.bottlesOfBeer();");
    std::cout << "--> " << value.toString() << "\n";
    value = scripting.evaluate("testobj.dynamicTest([3.5, {a: 100, b: 200}, 12], \"asd\");");
    std::cout << "--> " << value.toString() << "\n";
    value = scripting.evaluate("testobj.dynamicTest();");
    std::cout << "--> " << value.toString() << "\n";

    return 0;
}
