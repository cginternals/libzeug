#include <iostream>

#include <reflectionzeug/new/Typed.h>
#include <reflectionzeug/new/AccessorGetSet.h>
#include <reflectionzeug/new/AccessorValue.h>
#include <reflectionzeug/new/ArrayAccessorGetSet.h>
#include <reflectionzeug/new/ArrayAccessorValue.h>


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
        std::cout << "value = " << accessor.getValue() << " (1)\n";
        accessor.setValue(10);
        std::cout << "value = " << accessor.getValue() << " (10)\n";

        AccessorValue<int> accessor2(0);
        std::cout << "value = " << accessor2.getValue() << " (0)\n";
        accessor2.setValue(10);
        std::cout << "value = " << accessor2.getValue() << " (10)\n";

        std::cout << "\n";
    }

    // Create read-only accessor
    {
        std::cout << "Read-only accessor\n";

        AccessorGetSet<const int> accessor(&get);
        std::cout << "value = " << accessor.getValue() << " (10)\n";
        accessor.setValue(20);
        std::cout << "value = " << accessor.getValue() << " (10)\n";

        AccessorValue<const int> accessor2(0);
        std::cout << "value = " << accessor2.getValue() << " (0)\n";
        accessor2.setValue(20);
        std::cout << "value = " << accessor2.getValue() << " (0)\n";

        std::cout << "\n";
    }

    // Create read/write typed value
    {
        std::cout << "Read/write typed value\n";

        Typed<int> typeInt1(new AccessorGetSet<int>(&get, &set));
        Typed<int> typeInt2(&get, &set);

        long long l = typeInt1.toLongLong();

        std::cout << "value = " << typeInt1.getValue() << " (10)\n";
        typeInt1.setValue(20);
        std::cout << "value = " << typeInt2.getValue() << " (20)\n";

        std::cout << "\n";
    }

    // Create read-only typed value
    {
        std::cout << "Read-only typed value\n";

        Typed<const int> typeInt(&get);

        std::cout << "value = " << typeInt.getValue() << " (20)\n";
        typeInt.setValue(30);
        std::cout << "value = " << typeInt.getValue() << " (20)\n";

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

    // Create array-accessors
    {
        // Direct value
        std::cout << "Array accessor (direct value)\n";

        ArrayAccessorValue<int, 3> accessor1({1, 2, 3});
        std::cout << "value[0] = " << accessor1.getValue(0) << " (1)\n";
        std::cout << "value[1] = " << accessor1.getValue(1) << " (2)\n";
        std::cout << "value[2] = " << accessor1.getValue(2) << " (3)\n";

        accessor1.setValue(0, 10);
        std::cout << "value[0] = " << accessor1.getValue(0) << " (10)\n";
        std::cout << "value[1] = " << accessor1.getValue(1) << " (2)\n";
        std::cout << "value[2] = " << accessor1.getValue(2) << " (3)\n";

        accessor1.setValue(1, 10);
        std::cout << "value[0] = " << accessor1.getValue(0) << " (10)\n";
        std::cout << "value[1] = " << accessor1.getValue(1) << " (10)\n";
        std::cout << "value[2] = " << accessor1.getValue(2) << " (3)\n";

        accessor1.setValue(2, 10);
        std::cout << "value[0] = " << accessor1.getValue(0) << " (10)\n";
        std::cout << "value[1] = " << accessor1.getValue(1) << " (10)\n";
        std::cout << "value[2] = " << accessor1.getValue(2) << " (10)\n";

        std::cout << "\n";

        // Getter/setter
        std::cout << "Array accessor (getter/setter)\n";

        int v1 = 10, v2 = 11, v3 = 12;
        ArrayAccessorGetSet<int, 3> accessor2(
            [&] (size_t i) -> int {
                     if (i == 0) return v1;
                else if (i == 1) return v2;
                else if (i == 2) return v3;
                else             return 0;
            },

            [&] (size_t i, int value) {
                     if (i == 0) v1 = value;
                else if (i == 1) v2 = value;
                else if (i == 2) v3 = value;
            }
        );

        std::cout << "value[0] = " << accessor2.getValue(0) << " (10)\n";
        std::cout << "value[1] = " << accessor2.getValue(1) << " (11)\n";
        std::cout << "value[2] = " << accessor2.getValue(2) << " (12)\n";

        accessor2.setValue(0, 20);
        std::cout << "value[0] = " << accessor2.getValue(0) << " (20)\n";
        std::cout << "value[1] = " << accessor2.getValue(1) << " (11)\n";
        std::cout << "value[2] = " << accessor2.getValue(2) << " (12)\n";

        accessor2.setValue(1, 20);
        std::cout << "value[0] = " << accessor2.getValue(0) << " (20)\n";
        std::cout << "value[1] = " << accessor2.getValue(1) << " (20)\n";
        std::cout << "value[2] = " << accessor2.getValue(2) << " (12)\n";

        accessor2.setValue(2, 20);
        std::cout << "value[0] = " << accessor2.getValue(0) << " (20)\n";
        std::cout << "value[1] = " << accessor2.getValue(1) << " (20)\n";
        std::cout << "value[2] = " << accessor2.getValue(2) << " (20)\n";

        std::cout << "\n";
    }

    // Create array-value
    /*
    {
        std::cout << "Array value\n";

        Typed<std::array<int, 2>> typeArray;

//        std::cout << "value[0] = " << typeArray.getValue(0) << " (10)\n";
    }
    */
}
