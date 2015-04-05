#include <iostream>

#include <reflectionzeug/new/Typed.h>
#include <reflectionzeug/new/AccessorGetSet.h>
#include <reflectionzeug/new/AccessorValue.h>


using namespace reflectionzeug;


int globalInt = 1;

int get()
{
    return globalInt;
}

void set(int value)
{
    globalInt = value;
}

class TestClass {
public:
    static TestClass fromString(const std::string &str, bool * ok) {
        *ok = true;
        return TestClass();
    }

public:
    TestClass() {}
    ~TestClass() {}

    std::string toString() const
    {
        return "";
    }
};


int main(int argc, char *argv[])
{
    // Create read/write accessor
    {
        std::cout << "Read/write accessor\n";

        AccessorGetSet<int> accessor(&get, &set);
        std::cout << "value = " << accessor.get() << " (1)\n";
        accessor.set(10);
        std::cout << "value = " << accessor.get() << " (10)\n";

        AccessorValue<int> accessor2(0);
        std::cout << "value = " << accessor2.get() << " (0)\n";
        accessor2.set(10);
        std::cout << "value = " << accessor2.get() << " (10)\n";

        std::cout << "\n";
    }

    // Create read-only accessor
    {
        std::cout << "Read-only accessor\n";

        AccessorGetSet<const int> accessor(&get);
        std::cout << "value = " << accessor.get() << " (10)\n";
        accessor.set(20);
        std::cout << "value = " << accessor.get() << " (10)\n";

        AccessorValue<const int> accessor2(0);
        std::cout << "value = " << accessor2.get() << " (0)\n";
        accessor2.set(20);
        std::cout << "value = " << accessor2.get() << " (0)\n";

        std::cout << "\n";
    }

    // Create read/write typed value
    {
        std::cout << "Read/write typed value\n";

        Typed<int> typeInt1(new AccessorGetSet<int>(&get, &set));
        Typed<int> typeInt2(&get, &set);

        long long l = typeInt1.toLongLong();

        std::cout << "value = " << typeInt1.get() << " (10)\n";
        typeInt1.set(20);
        std::cout << "value = " << typeInt2.get() << " (20)\n";

        std::cout << "\n";
    }

    // Create read-only typed value
    {
        std::cout << "Read-only typed value\n";

        Typed<const int> typeInt(&get);

        std::cout << "value = " << typeInt.get() << " (20)\n";
        typeInt.set(30);
        std::cout << "value = " << typeInt.get() << " (20)\n";

        std::cout << "\n";
    }

    // Check other data types
    {
        Typed<int>          typeInt;
        Typed<unsigned int> typeUInt;
        Typed<float>        typeFloat;
        Typed<double>       typeDouble;
        Typed<bool>         typeBool;
        Typed<std::string>  typeString;
        Typed<Color>        typeColor;
        Typed<FilePath>     typeFilePath;
        Typed<TestClass>    typeTestClass;
    }
}
