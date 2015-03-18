#include <string>

#include <QApplication>
#include <QWidget>
#include <QPushButton>

#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>

#include <propertyguizeug/PropertyBrowser.h>

//#include <widgetzeug/ColorGradient.h>
//#include <widgetzeug/ColorGradientProperty.h>
#include <widgetzeug/dark_fusion_style.hpp>

using namespace reflectionzeug;
using namespace propertyguizeug;
using namespace widgetzeug;

enum class MyEnum { One, Two, Three };

template <typename T>
std::function<T()> getter(const T & value)
{
    return [&value]() { return value; };
}

template <typename T>
std::function<void(const T &)> setter(T & value)
        {
    return [&value](const T & newValue) { value = newValue; };
}

template <typename T>
Property<T> * newProperty(const std::string & name, T & value)
                {
    return new Property<T>(name, getter(value), setter(value));
}

void addFlagProperty(PropertyGroup * group, bool & flagValue, const std::string & flag)
{
    group->addProperty<bool>(flag, getter(flagValue), setter(flagValue))->valueChanged.connect(
        [&flag, group] (bool b)
        {
            group->forEachGroup(
                [&flag, b] (PropertyGroup & subGroup)
                {
                    if (b)
                        subGroup.setOption(flag, true);
                    else
                        subGroup.setOption(flag, false);
                });
        });
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("property_editors");
    QApplication::setOrganizationName("hpicgs_libzeug");
    
    enableDarkFusionStyle();
    
    PropertyGroup group;
    
    auto readonlyValue = false;
    auto disabledValue = false;
    addFlagProperty(&group, readonlyValue, "readonly");
    addFlagProperty(&group, disabledValue, "disabled");
    
    PropertyGroup * subGroup;
    
    subGroup = group.addGroup("floating_point");
    
    auto floatValue = 2.0f;
    auto floatProperty = newProperty("float", floatValue);
    floatProperty->setOptions({
        { "minimum", Variant(1.2f) },
        { "maximum", Variant(13.0f) },
        { "step", Variant(0.5f) },
        { "precision", Variant(1u) }
    });
    subGroup->addProperty(floatProperty);
    
    auto doubleValue = 0.0;
    auto doubleProperty = newProperty("double", doubleValue);
    doubleProperty->setOptions({
        { "minimum", Variant(-1.0) },
        { "maximum", Variant(1.0) },
        { "step", Variant(0.01) },
        { "precision", Variant(2u) }
    });
    subGroup->addProperty(doubleProperty);
    
    subGroup = group.addGroup("signed_integrals");
    
    auto charValue = static_cast<char>(1);
    auto charProperty = newProperty("char", charValue);
    charProperty->setOptions({
        { "minimum", Variant(-1) },
        { "maximum", Variant(2) },
        { "step", Variant(1) }
    });
    subGroup->addProperty(charProperty);
    
    auto shortValue = static_cast<short>(2);
    auto shortProperty = newProperty("short", shortValue);
    shortProperty->setOptions({
        { "minimum", Variant(-2) },
        { "maximum", Variant(3) },
        { "step", Variant(1) }
    });
    subGroup->addProperty(shortProperty);
    
    auto intValue = 3;
    auto intProperty = newProperty("int", intValue);
    shortProperty->setOptions({
        { "minimum", Variant(-3) },
        { "maximum", Variant(4) },
        { "step", Variant(1) }
    });
    subGroup->addProperty(intProperty);
    
    auto longValue = 4l;
    auto longProperty = newProperty("long", longValue);
    longProperty->setOptions({
        { "minimum", Variant(-4l) },
        { "maximum", Variant(5l) },
        { "step", Variant(1l) }
    });
    subGroup->addProperty(longProperty);
    
    auto longLongValue = 5ll;
    auto longLongProperty = newProperty("longlong", longLongValue);
    longLongProperty->setOptions({
        { "minimum", Variant(-5ll) },
        { "maximum", Variant(6ll) },
        { "step", Variant(1ll) }
    });
    subGroup->addProperty(longLongProperty);
    
    subGroup = group.addGroup("unsigned_integrals");
    
    auto uCharValue = static_cast<unsigned char>(0u);
    auto uCharProperty = newProperty("uchar", uCharValue);
    uCharProperty->setOptions({
        { "minimum", Variant(0u) },
        { "maximum", Variant(10u) },
        { "step", Variant(1u) }
    });
    subGroup->addProperty(uCharProperty);
    
    auto uShortValue = static_cast<unsigned short>(0u);
    auto uShortProperty = newProperty("ushort", uShortValue);
    uShortProperty->setOptions({
        { "minimum", Variant(0u) },
        { "maximum", Variant(20u) },
        { "step", Variant(2u) }
    });
    subGroup->addProperty(uShortProperty);
    
    auto uIntValue = 0u;
    auto uIntProperty = newProperty("uint", uIntValue);
    uIntProperty->setOptions({
        { "minimum", Variant(0u) },
        { "maximum", Variant(30u) },
        { "step", Variant(3u) }
    });
    subGroup->addProperty(uIntProperty);
    
    auto uLongValue = 0ul;
    auto uLongProperty = newProperty("ulong", uLongValue);
    uLongProperty->setOptions({
        { "minimum", Variant(0ul) },
        { "maximum", Variant(40ul) },
        { "step", Variant(4ul) }
    });
    subGroup->addProperty(uLongProperty);
    
    auto uLongLongValue = 0ull;
    auto uLongLongProperty = newProperty("ulonglong", uLongLongValue);
    uLongLongProperty->setOptions({
        { "minimum", Variant(0ull) },
        { "maximum", Variant(50ull) },
        { "step", Variant(5ull) }
    });
    subGroup->addProperty(uLongLongProperty);
    
    subGroup = group.addGroup("string");
    
    auto stringValue = std::string{"Hallo Welt!"};
    auto stringProperty = newProperty("std_string", stringValue);
    subGroup->addProperty(stringProperty);
    
    auto choicesValue = false;
    auto choicesProperty = newProperty("choices", choicesValue);
    choicesProperty->valueChanged.connect(
        [stringProperty] (bool b)
        {
            if (b)
                stringProperty->setOption("choices", std::vector<std::string>({ "blau", "rot", "grün" }));
            else
                stringProperty->removeOption("choices");
        });
    subGroup->addProperty(choicesProperty);
        
    subGroup = group.addGroup("other"); 

    auto filePathValue = FilePath{};
    auto filePathProperty = newProperty("file_path", filePathValue);
    filePathProperty->setOptions({
        { "uniqueidentifier", "filePath" }
    });
    subGroup->addProperty(filePathProperty);
    
    auto colorValue = Color{128, 128, 128};
    auto colorProperty = newProperty("color", colorValue);
    subGroup->addProperty(colorProperty);
    
    auto enumValue = MyEnum::One;
    auto enumProperty = newProperty("enum", enumValue);
    enumProperty->setStrings({
        { MyEnum::One, "One" },
        { MyEnum::Two, "Two" },
        { MyEnum::Three, "Three" }
    });
    subGroup->addProperty(enumProperty);
    
    //auto colorGradientValue = ColorGradient::fromList({ QColor{Qt::black}, QColor{Qt::white} });
    //auto colorGradientProperty = newProperty("gradient", colorGradientValue);
    //subGroup->addProperty(colorGradientProperty);

    PropertyBrowser browser;
    browser.setRoot(&group);
    browser.show();

    return a.exec();
}
