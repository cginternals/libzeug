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
        AccessorGetSet<int> accessor(&get, &set);
        std::cout << "value = " << accessor.get() << "\n";
        accessor.set(10);
        std::cout << "value = " << accessor.get() << "\n";
    }

    // Create read-only accessor
    {
        AccessorGetSet<const int> accessor(&get);
        std::cout << "value = " << accessor.get() << "\n";
        accessor.set(20);
        std::cout << "value = " << accessor.get() << "\n";
    }

    // Create simple type instance
    {
        AccessorGetSet<int> accessor(&get, &set);
        Typed< int, AccessorGetSet<int> > typeInt (accessor);
        Typed< int, AccessorGetSet<int> > typeInt2(AccessorGetSet<int>(&get, &set));
    }
}
