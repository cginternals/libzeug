#include <iostream>

#include <reflectionzeug/new/Type.h>
#include <reflectionzeug/new/TypeInt.h>
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
        Type< int, AccessorGetSet<int> > typeInt (accessor);
        Type< int, AccessorGetSet<int> > typeInt2(AccessorGetSet<int>(&get, &set));
    }
}
