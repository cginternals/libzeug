
#include <iostream>
#include <sstream>

#include <reflectionzeug/property/AccessorGetSet.h>
#include <reflectionzeug/property/AccessorValue.h>
#include <reflectionzeug/property/ArrayAccessorGetSet.h>
#include <reflectionzeug/property/ArrayAccessorValue.h>
#include <reflectionzeug/property/Visitor.h>
#include <reflectionzeug/property/Property.h>
#include <reflectionzeug/property/PropertyGroup.h>
#include <reflectionzeug/variant/Variant.h>
#include <reflectionzeug/tools/SerializerJSON.h>
#include <reflectionzeug/tools/SerializerINI.h>


using namespace reflectionzeug;


void printVariant(const Variant & var, const std::string & indent = "")
{
    for (auto attr : *var.asMap()) {
        std::string name  = attr.first;
        const Variant & value = attr.second;

        if (value.isMap()) {
            printVariant(value, indent + "    ");
        } else {
            std::stringstream s;
                 if (value.hasType<std::string>()) s << value.value<std::string>();
            else if (value.hasType<int>())         s << value.value<int>();
            else if (value.hasType<float>())       s << value.value<float>();

            std::cout << indent << "- " << name << " = " << s.str() << "\n";
        }
    }
}


// Global getter/setter test
int         globalInt    = 1;
float       globalFloat  = 3.2f;
std::string globalString = "test";

int getInt()
{
    return globalInt;
}

void setInt(int value)
{
    globalInt = value;
}

float getFloat()
{
    return globalFloat;
}

void setFloat(float value)
{
    globalFloat = value;
}

std::string getString()
{
    return globalString;
}

void setString(const std::string & value)
{
    globalString = value;
}

// Global array getter/setter
int v1 = 10, v2 = 11, v3 = 12;

int getArray(size_t i)
{
         if (i == 0) return v1;
    else if (i == 1) return v2;
    else if (i == 2) return v3;
    else             return 0;
}

void setArray(size_t i, int value)
{
         if (i == 0) v1 = value;
    else if (i == 1) v2 = value;
    else if (i == 2) v3 = value;
}

// Custom class test
class TestClass {
public:
    static TestClass fromString(const std::string & str, bool * ok) {
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

// Enum test
enum MyEnum {
    One = 1,
    Two,
    Three
};

namespace reflectionzeug
{

template <>
struct EnumDefaultStrings<MyEnum>
{
    std::map<MyEnum, std::string> operator()()
    {
        std::map<MyEnum, std::string> values = {
            {One,   "One"},
            {Two,   "Two"},
            {Three, "Three"}
        };

        return values;
    }
};

}

// Visitor test
class MyVisitor : public reflectionzeug::Visitor<
                            AbstractCollection,
                            AbstractSignedIntegralInterface,
                            AbstractUnsignedIntegralInterface,
                            AbstractFloatingPointInterface,
                            AbstractBooleanInterface,
                            AbstractStringInterface,
                            AbstractColorInterface,
                            AbstractEnumInterface,
                            PropertySignedIntegral<int>,
                            PropertyUnsignedIntegral<unsigned int>,
                            PropertyFloatingPoint<float>,
                            PropertyFloatingPoint<double>,
                            PropertyBool,
                            PropertyString,
                            PropertyColor,
                            PropertyFilePath,
                            PropertyEnum<MyEnum>,
                            PropertyArray<int, 3>,
                            Property<int>,
                            Property<unsigned int>,
                            Property<float>,
                            Property<double>,
                            Property<bool>,
                            Property<std::string>,
                            Property<FilePath>,
                            Property<Color>,
                            Property<MyEnum>,
                            Property<std::array<int, 3>>,
                            PropertyGroup >
{
public:
    virtual void visit(AbstractCollection * prop) override
    {
        std::cout << "found AbstractCollection\n";
    }

    virtual void visit(AbstractSignedIntegralInterface * prop) override
    {
        std::cout << "found SignedIntegralInterface\n";
    }

    virtual void visit(AbstractUnsignedIntegralInterface * prop) override
    {
        std::cout << "found AbstractUnsignedIntegralInterface\n";
    }

    virtual void visit(AbstractFloatingPointInterface * prop) override
    {
        std::cout << "found AbstractFloatingPointInterface\n";
    }

    virtual void visit(AbstractBooleanInterface * prop) override
    {
        std::cout << "found AbstractBooleanInterface\n";
    }

    virtual void visit(AbstractStringInterface * prop) override
    {
        std::cout << "found AbstractStringInterface\n";
    }

    virtual void visit(AbstractColorInterface * prop) override
    {
        std::cout << "found AbstractColorInterface\n";
    }

    virtual void visit(AbstractEnumInterface * prop) override
    {
        std::cout << "found AbstractEnumInterface\n";
    }

    virtual void visit(PropertySignedIntegral<int> * prop) override
    {
        std::cout << prop->name() << " PropertySignedIntegral<int>\n";
    }

    virtual void visit(PropertyUnsignedIntegral<unsigned int> * prop) override
    {
        std::cout << prop->name() << " PropertyUnsignedIntegral<unsigned int>\n";
    }

    virtual void visit(PropertyFloatingPoint<float> * prop) override
    {
        std::cout << prop->name() << " PropertyFloatingPoint<float>\n";
    }

    virtual void visit(PropertyFloatingPoint<double> * prop) override
    {
        std::cout << prop->name() << " PropertyFloatingPoint<double>\n";
    }

    virtual void visit(PropertyBool * prop) override
    {
        std::cout << prop->name() << " PropertyBool\n";
    }

    virtual void visit(PropertyString * prop) override
    {
        std::cout << prop->name() << " PropertyString\n";
    }

    virtual void visit(PropertyColor * prop) override
    {
        std::cout << prop->name() << " PropertyColor\n";
    }

    virtual void visit(PropertyFilePath * prop) override
    {
        std::cout << prop->name() << " PropertyFilePath\n";
    }

    virtual void visit(PropertyEnum<MyEnum> * prop) override
    {
        std::cout << prop->name() << " PropertyEnum<MyEnum>\n";
    }

    virtual void visit(PropertyArray<int, 3> * prop) override
    {
        std::cout << prop->name() << " PropertyArray<int, 3>\n";
    }

    virtual void visit(Property<int> * prop) override
    {
        std::cout << prop->name() << " Property<int>\n";
    }

    virtual void visit(Property<unsigned int> * prop) override
    {
        std::cout << prop->name() << " Property<unsigned int>\n";
    }

    virtual void visit(Property<float> * prop) override
    {
        std::cout << prop->name() << " Property<float>\n";
    }

    virtual void visit(Property<double> * prop) override
    {
        std::cout << prop->name() << " Property<double>\n";
    }

    virtual void visit(Property<bool> * prop) override
    {
        std::cout << prop->name() << " Property<bool>\n";
    }

    virtual void visit(Property<std::string> * prop) override
    {
        std::cout << prop->name() << " Property<std::string>\n";
    }

    virtual void visit(Property<Color> * prop) override
    {
        std::cout << prop->name() << " Property<Color>\n";
    }

    virtual void visit(Property<FilePath> * prop) override
    {
        std::cout << prop->name() << " Property<FilePath>\n";
    }

    virtual void visit(Property<MyEnum> * prop) override
    {
        std::cout << prop->name() << " Property<MyEnum>\n";
    }

    virtual void visit(Property<std::array<int, 3>> * prop) override
    {
        std::cout << prop->name() << " Property<std::array<int, 3>>\n";
    }

    virtual void visit(PropertyGroup * group) override
    {
        std::cout << group->name() << " PropertyGroup\n";
    }
};

void print(PropertyGroup * group, std::string indent = "")
{
    std::cout << indent << group->name() << ": {\n";

    for (std::pair<std::string, AbstractProperty *> it : group->properties())
    {
        AbstractProperty * property = it.second;
        if (property->isGroup())
        {
            print(property->asGroup(), indent + "  ");
        }
        else
        {
            std::cout << indent << "  " << property->name() << "\n";
        }
    }

    std::cout << indent << "}\n";
}

int main(int argc, char *argv[])
{
    // Create read/write accessor
    {
        std::cout << "Read/write accessor\n";

        AccessorGetSet<int> accessor(&getInt, &setInt);
        std::cout << "value = " << accessor.value() << " (1)\n";
        accessor.setValue(10);
        std::cout << "value = " << accessor.value() << " (10)\n";

        AccessorValue<int> accessor2(0);
        std::cout << "value = " << accessor2.value() << " (0)\n";
        accessor2.setValue(10);
        std::cout << "value = " << accessor2.value() << " (10)\n";

        std::cout << "\n";
    }

    // Create read-only accessor
    {
        std::cout << "Read-only accessor\n";

        AccessorGetSet<const int> accessor(&getInt);
        std::cout << "value = " << accessor.value() << " (10)\n";
        accessor.setValue(20);
        std::cout << "value = " << accessor.value() << " (10)\n";

        AccessorValue<const int> accessor2(0);
        std::cout << "value = " << accessor2.value() << " (0)\n";
        accessor2.setValue(20);
        std::cout << "value = " << accessor2.value() << " (0)\n";

        std::cout << "\n";
    }

    // Create read/write property
    {
        std::cout << "Read/write property\n";

        Property<int> propInt1("int1", new AccessorGetSet<int>(&getInt, &setInt));
        Property<int> propInt2("int1", &getInt, &setInt);

        long long l = propInt1.toLongLong();

        std::cout << "value = " << propInt1.value() << " (10)\n";
        propInt1.setValue(20);
        std::cout << "value = " << propInt2.value() << " (20)\n";

        std::cout << "\n";
    }

    // Create read-only property
    {
        std::cout << "Read-only property\n";

        Property<const int> propInt("int", &getInt);

        std::cout << "value = " << propInt.value() << " (20)\n";
        propInt.setValue(30);
        std::cout << "value = " << propInt.value() << " (20)\n";

        std::cout << "\n";
    }

    // Check other data types
    {
        Property<int>          propInt("");
        Property<unsigned int> propUInt("");
        Property<float>        propFloat("");
        Property<double>       propDouble("");
        Property<bool>         propBool("");
        Property<std::string>  propString("");
        Property<Color>        propColor("");
        Property<FilePath>     propFilePath("");
    }

    // Check error for unsupported property types
    {
        // This has to throw a compiler error!
        //Property<TestClass>    propTestClass("");
    }

    // Create array-accessors
    {
        // Direct value
        std::cout << "Array accessor (direct value)\n";

        ArrayAccessorValue<int, 3> accessor1({1, 2, 3});
        std::cout << "value[0] = " << accessor1.getElement(0) << " (1)\n";
        std::cout << "value[1] = " << accessor1.getElement(1) << " (2)\n";
        std::cout << "value[2] = " << accessor1.getElement(2) << " (3)\n";

        accessor1.setElement(0, 10);
        std::cout << "value[0] = " << accessor1.getElement(0) << " (10)\n";
        std::cout << "value[1] = " << accessor1.getElement(1) << " (2)\n";
        std::cout << "value[2] = " << accessor1.getElement(2) << " (3)\n";

        accessor1.setElement(1, 10);
        std::cout << "value[0] = " << accessor1.getElement(0) << " (10)\n";
        std::cout << "value[1] = " << accessor1.getElement(1) << " (10)\n";
        std::cout << "value[2] = " << accessor1.getElement(2) << " (3)\n";

        accessor1.setElement(2, 10);
        std::cout << "value[0] = " << accessor1.getElement(0) << " (10)\n";
        std::cout << "value[1] = " << accessor1.getElement(1) << " (10)\n";
        std::cout << "value[2] = " << accessor1.getElement(2) << " (10)\n";

        std::cout << "\n";

        // Getter/setter
        std::cout << "Array accessor (getter/setter)\n";

        ArrayAccessorGetSet<int, 3> accessor2(getArray, setArray);

        std::cout << "value[0] = " << accessor2.getElement(0) << " (10)\n";
        std::cout << "value[1] = " << accessor2.getElement(1) << " (11)\n";
        std::cout << "value[2] = " << accessor2.getElement(2) << " (12)\n";

        accessor2.setElement(0, 20);
        std::cout << "value[0] = " << accessor2.getElement(0) << " (20)\n";
        std::cout << "value[1] = " << accessor2.getElement(1) << " (11)\n";
        std::cout << "value[2] = " << accessor2.getElement(2) << " (12)\n";

        accessor2.setElement(1, 21);
        std::cout << "value[0] = " << accessor2.getElement(0) << " (20)\n";
        std::cout << "value[1] = " << accessor2.getElement(1) << " (21)\n";
        std::cout << "value[2] = " << accessor2.getElement(2) << " (12)\n";

        accessor2.setElement(2, 22);
        std::cout << "value[0] = " << accessor2.getElement(0) << " (20)\n";
        std::cout << "value[1] = " << accessor2.getElement(1) << " (21)\n";
        std::cout << "value[2] = " << accessor2.getElement(2) << " (22)\n";

        std::cout << "\n";
    }

    // Create array-value
    {
        std::cout << "Array value\n";

        Property<std::array<int, 3>> propArray("array", getArray, setArray);

        std::cout << "value.empty = " << (propArray.isEmpty() ? "yes (no)\n" : "no (no)\n");
        std::cout << "value.size = " << propArray.count() << " (3)\n";
        std::cout << "value[0] = " << propArray.getElement(0) << " (20)\n";
        std::cout << "value[1] = " << propArray.getElement(1) << " (21)\n";
        std::cout << "value[2] = " << propArray.getElement(2) << " (22)\n";

        propArray.forEach([] (AbstractProperty & prop) {
            AbstractTypedProperty<int> & intProp = static_cast<AbstractTypedProperty<int> &>(prop);
            intProp.setValue(100);
        });

        std::cout << "value.empty = " << (propArray.isEmpty() ? "yes (no)\n" : "no (no)\n");
        std::cout << "value.size = " << propArray.count() << " (3)\n";
        std::cout << "value[0] = " << propArray.getElement(0) << " (100)\n";
        std::cout << "value[1] = " << propArray.getElement(1) << " (100)\n";
        std::cout << "value[2] = " << propArray.getElement(2) << " (100)\n";

        std::cout << "\n";
    }

    // Create enum-value
    {
        std::cout << "Enum value\n";

        Property<MyEnum> propEnum("enum");
        propEnum.setValue(One);
        std::cout << "value = " << propEnum.value() << " '" << propEnum.toString() << "'" << " (1 'One')\n";

        propEnum.setValue((MyEnum)2);
        std::cout << "value = " << propEnum.value() << " '" << propEnum.toString() << "'" << " (2 'Two')\n";

        propEnum.fromString("Three");
        std::cout << "value = " << propEnum.value() << " '" << propEnum.toString() << "'" << " (3 'Three')\n";

        std::cout << "\n";
    }

    // Test visitor
    {
        std::cout << "Visitor test\n";

        MyVisitor visitor;

        Property<int> propInt;
        propInt.accept(&visitor);

        Property<unsigned int> propUInt;
        propUInt.accept(&visitor);

        Property<float> propFloat;
        propFloat.accept(&visitor);

        Property<double> propDouble;
        propDouble.accept(&visitor);

        Property<bool> propBool;
        propBool.accept(&visitor);

        Property<std::string> propString;
        propString.accept(&visitor);

        Property<Color> propColor;
        propColor.accept(&visitor);

        Property<FilePath> propFilePath;
        propFilePath.accept(&visitor);

        Property<MyEnum> propMyEnum;
        propMyEnum.accept(&visitor);

        Property<std::array<int, 3>> propArray("array", std::array<int, 3>{0, 0, 0});
        propArray.accept(&visitor);

        Property<int> propertyInt("Integer");
        propertyInt.accept(&visitor);

        PropertyGroup group("group");
        group.accept(&visitor);

        std::cout << "\n";
    }

    // Create changed-signal
    {
        std::cout << "Signal test\n";

        Property<int> propInt;
        propInt.changed.connect([] () {
            std::cout << "propInt changed.\n";
        });

        for (int i=0; i<10; i++) {
            propInt.setValue(i);
            std::cout << "value = " << propInt.value() << " (" << i << ")\n";
        }

        std::cout << "\n";
    }

    // Casting test
    {
        std::cout << "Casting test\n";

        AbstractProperty * propertyInt = new Property<int>("int");
        if (propertyInt->isCollection()) {
            std::cout << "propertyInt is a collection.\n";
        } else {
            std::cout << "propertyInt is NOT a collection.\n";
        }
        if (propertyInt->isGroup()) {
            std::cout << "propertyInt is a group.\n";
        } else {
            std::cout << "propertyInt is NOT a group.\n";
        }

        AbstractProperty * propertyArray = new Property<std::array<int, 3>>("array");
        if (propertyArray->isCollection()) {
            std::cout << "propertyArray is a collection.\n";
        } else {
            std::cout << "propertyArray is NOT a collection.\n";
        }
        if (propertyArray->isGroup()) {
            std::cout << "propertyArray is a group.\n";
        } else {
            std::cout << "propertyArray is NOT a group.\n";
        }

        std::cout << "\n";
    }

    // Property group test
    {
        std::cout << "Group test:\n";
        std::cout << "\n";

        PropertyGroup * sub1 = new PropertyGroup("sub1");
        sub1->addProperty<int>("number", &getInt, &setInt);
        sub1->addProperty<float>("float", &getFloat, &setFloat);
        sub1->addProperty<std::string>("string", &getString, &setString);

        PropertyGroup * sub2 = new PropertyGroup("sub2");
        sub2->addProperty<int>("number", &getInt, &setInt);
        sub2->addProperty<float>("float", &getFloat, &setFloat);
        sub2->addProperty<std::string>("string", &getString, &setString);

        PropertyGroup * root = new PropertyGroup("root");
        root->addProperty<int>("number", &getInt, &setInt);
        root->addProperty<float>("float", &getFloat, &setFloat);
        root->addProperty<std::string>("string", &getString, &setString);
        root->addProperty(sub1);
        root->addProperty(sub2);

        print(root);

        std::cout << "\n";


        std::cout << "Group visitor test:\n";

        MyVisitor visitor;
        root->acceptRecursive(&visitor);

        std::cout << "\n";
    }

    // Variant test
    {
        Variant var = 10;

        int i = var.value<int>();
        std::cout << "i = " << i << "\n";

        int * pi = var.ptr<int>();
        std::cout << "*pi = " << *pi << "\n";
    }

    // Variant map test
    {
        Variant var = Variant::map();
        (*var.asMap())["eins"] = 1.01f;
        (*var.asMap())["zwei"] = 2;
        (*var.asMap())["drei"] = "3";
        (*var.asMap())["vier"] = Variant::map();
        (*var.asMap())["ja"]   = true;
        (*var.asMap())["nein"] = false;
        (*(*var.asMap())["vier"].asMap())["a"] = 1;
        (*(*var.asMap())["vier"].asMap())["b"] = 2;
        (*(*var.asMap())["vier"].asMap())["c"] = 3;
        (*(*var.asMap())["vier"].asMap())["d"] = 4;

        std::cout << "var.isMap() = " << (var.isMap() ? "true" : "false") << "\n";
        printVariant(var);
        std::cout << "\n";

        {
            SerializerJSON json;
            std::cout << json.toString(var) << "\n";
            std::cout << "\n";
        }

        {
            SerializerJSON json(SerializerJSON::Beautify);
            std::cout << json.toString(var) << "\n";
            std::cout << "\n";
        }

        {
            SerializerINI ini;
            ini.save(var, "test.ini");
        }
    }

    // INI test
    {
        SerializerINI ini;
        Variant var;

        ini.load(var, "test.ini");

        SerializerJSON json(SerializerJSON::Beautify);
        std::cout << json.toString(var) << "\n";
        std::cout << "\n";
    }

    // JSON test
    /*
    {
        SerializerJSON json(SerializerJSON::Beautify);
        Variant var;

        json.load(var, "/workspace/hpi/projects/gtx/data/datasets/berlin/flow/berlin_flow_2015_01_02-20_29_46.json");

        SerializerINI ini;
        std::cout << ini.toString(var) << "\n";
        std::cout << "\n";
    }
    */
}
