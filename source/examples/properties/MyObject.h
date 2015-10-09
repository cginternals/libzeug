
#pragma once


#include <array>

#include <reflectionzeug/Object.h>


enum class MyEnum : char { Value1, Value2, Value3 };


class MyObject : public reflectionzeug::Object
{
public:
    MyObject();

    int intValue() const;
    void setIntValue(const int & value);

    MyEnum enumValue() const;
    void setEnumValue(MyEnum value);

    float floatArrayAt(size_t i) const;
    void setFloatArrayAt(size_t i, float elementl);

private:
    int m_intValue;
    MyEnum m_enumValue;
    std::array<float, 3> m_floatArray;
    bool m_boolValue;
};


namespace reflectionzeug {


// Define string mapping for MyEnum.
// Will be used in fromString() / toString() methods.
template <>
struct EnumDefaultStrings<MyEnum>
{
    std::map<MyEnum, std::string> operator()()
    {
        return
        {
            { MyEnum::Value1, "Value1" },
            { MyEnum::Value2, "Value2" },
            { MyEnum::Value3, "Value3" },
        };
    }
};


} // namespace reflectionzeug
