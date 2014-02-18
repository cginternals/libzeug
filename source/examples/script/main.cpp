#include <iostream>
#include <scriptzeug/ScriptContext.h>
#include <scriptzeug/Object.h>


using namespace scriptzeug;


Variant testFunction(std::string a)
{
    std::cout << "Test function\n";

    Variant value = Variant::Object();
    value.set("a", 1);
    value.set("b", 2);
    value.set("c", 3);
    value.set("d", "end");
    return value;
}


class Counting : public Object
{
public:
    Counting() : Object("counting"), m_min(0), m_max(2)
    {
        addProperty<int>("min", *this, &Counting::getMin, &Counting::setMin);
        addProperty<int>("max", *this, &Counting::getMax, &Counting::setMax);
        addFunction("count", this, &Counting::count);
    }

    ~Counting()
    {
    }

    void count()
    {
        for (int i=m_min; i<=m_max; i++) {
            std::cout << "Counting " << i << " ...\n";
        }
    }

    int getMin() const { return m_min; }
    void setMin(const int &min) { m_min = min; }
    int getMax() const { return m_max; }
    void setMax(const int & max) { m_max = max; }

protected:
    int m_min, m_max;
};


class MyInterface : public Object
{
public:
    MyInterface() : Object("api"), m_prompt("Hello World")
    {
        // Properties
        addProperty<std::string>("prompt", *this, &MyInterface::prompt, &MyInterface::setPrompt);
        addGroup(new Counting);

        // Functions
        addFunction("test",                &testFunction);
        addFunction("helloWorld",    this, &MyInterface::helloWorld);
        addFunction("bottlesOfBeer", this, &MyInterface::bottlesOfBeer);
        addFunction("dynamicTest",   this, &MyInterface::dynamicTest);
    }

    ~MyInterface()
    {
    }

    int helloWorld()
    {
        std::cout << m_prompt << "\n";
        return 10;
    }

    std::string bottlesOfBeer(int count, float a)
    {
        std::cout << count << " bottles of beer with " << a << "% volume.\n";
        return "hicks";
    }

    void dynamicTest(const std::vector<Variant> &args)
    {
        std::cout << "Number of arguments: " << args.size() << "\n";

        int i=0;
        for (std::vector<Variant>::const_iterator it = args.begin(); it != args.end(); ++it) {
            std::cout << "- " << i << ": " << (*it).toString() << "\n";
            i++;
        }
    }

protected:
    std::string prompt() const
    {
        return m_prompt;
    }

    void setPrompt(const std::string & prompt)
    {
        m_prompt = prompt;
    }

protected:
    std::string m_prompt;
};


int main(int argc, char const *argv[])
{
    MyInterface obj;

    ScriptContext scripting;
    scripting.registerObject(&obj);

    Variant value;

    value = scripting.evaluate("1 + 2");
    std::cout << "--> " << value.toString() << "\n";

    value = scripting.evaluate("api.prompt = 'Welcome!';");
    std::cout << "--> " << value.toString() << "\n";

    value = scripting.evaluate("api.helloWorld() + 1;");
    std::cout << "--> " << value.toString() << "\n";

    value = scripting.evaluate("api.test();");
    std::cout << "--> " << value.toString() << "\n";

    value = scripting.evaluate("api.bottlesOfBeer(120, 3.5, 10);");
    std::cout << "--> " << value.toString() << "\n";

    value = scripting.evaluate("api.bottlesOfBeer();");
    std::cout << "--> " << value.toString() << "\n";

    value = scripting.evaluate("api.dynamicTest([3.5, {a: 100, b: 200}, 12], \"asd\");");
    std::cout << "--> " << value.toString() << "\n";

    value = scripting.evaluate("api.dynamicTest();");
    std::cout << "--> " << value.toString() << "\n";

    value = scripting.evaluate("api.counting.min;");
    std::cout << "--> " << value.toString() << "\n";

    value = scripting.evaluate("api.counting.max;");
    std::cout << "--> " << value.toString() << "\n";

    value = scripting.evaluate("api.counting.min = 5;");
    value = scripting.evaluate("api.counting.max = 10;");
    value = scripting.evaluate("api.counting.count();");
    std::cout << "--> " << value.toString() << "\n";

    return 0;
}
