#include <iostream>

#include <reflectionzeug/new/Typed.h>
#include <reflectionzeug/new/TypedInt.h>
#include <reflectionzeug/new/AccessorGetSet.h>


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

int main(int argc, char *argv[])
{
    // Create read/write accessor
    {
        std::cout << "Read/write accessor\n";

        AccessorGetSet<int> accessor(&get, &set);
        std::cout << "value = " << accessor.get() << " (1)\n";
        accessor.set(10);
        std::cout << "value = " << accessor.get() << " (10)\n";

        std::cout << "\n";
    }

    // Create read-only accessor
    {
        std::cout << "Read-only accessor\n";

        AccessorGetSet<const int> accessor(&get);
        std::cout << "value = " << accessor.get() << " (10)\n";
        accessor.set(20);
        std::cout << "value = " << accessor.get() << " (10)\n";

        std::cout << "\n";
    }

    // Create read/write typed value
    {
        std::cout << "Read/write typed value\n";

        AccessorGetSet<int> accessor(&get, &set);
        Typed< int, AccessorGetSet<int> > typeInt1(accessor);
        Typed< int, AccessorGetSet<int> > typeInt2(AccessorGetSet<int>(&get, &set));
        Typed< int, AccessorGetSet<int> > typeInt3(&get, &set);

        std::cout << "value = " << typeInt1.get() << " (10)\n";
        typeInt2.set(20);
        std::cout << "value = " << typeInt3.get() << " (20)\n";

        std::cout << "\n";
    }

    // Create read-only typed value
    {
        std::cout << "Read-only typed value\n";

        Typed< int, AccessorGetSet<const int> > typeInt(&get);

        std::cout << "value = " << typeInt.get() << " (20)\n";
        typeInt.set(30);
        std::cout << "value = " << typeInt.get() << " (20)\n";

        std::cout << "\n";
    }
}
