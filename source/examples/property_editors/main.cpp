
#include <string>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <propertyguizeug/PropertyBrowser.h>


using namespace reflectionzeug;
using namespace propertyguizeug;

void addFlagProperty(PropertyGroup * group, const std::string & flag)
{
    group->addProperty<bool>(flag, false)->valueChanged.connect([&flag, group] (bool b)
        {
            group->forEachGroup([&flag, b] (PropertyGroup & subGroup)
                {
                    if (b)
                        subGroup.addFlag(flag);
                    else
                        subGroup.removeFlag(flag);
                });
        });
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("property_editors");
    QApplication::setOrganizationName("hpicgs_libzeug");
    
    PropertyGroup group;
    
    addFlagProperty(&group, "readonly");
    addFlagProperty(&group, "disabled");
    
    PropertyGroup * subGroup;
    
    subGroup = group.addGroup("floating_point");
    
    subGroup->addProperty<float>("float", 2.0f)->setOptions({
        { "minimum", Variant(1.2f) },
        { "maximum", Variant(13.0f) },
        { "step", Variant(0.5f) },
        { "precision", Variant(1u) }
    });
    
    subGroup->addProperty<double>("double", 0.0)->setOptions({
        { "minimum", Variant(-1.0) },
        { "maximum", Variant(1.0) },
        { "step", Variant(0.01) },
        { "precision", Variant(2u) }
    });
    
    subGroup = group.addGroup("signed_integrals");
    
    subGroup->addProperty<char>("char", 1)->setOptions({
        { "minimum", Variant(-1) },
        { "maximum", Variant(2) },
        { "step", Variant(1) }
    });
    
    subGroup->addProperty<short>("short", 2)->setOptions({
        { "minimum", Variant(-2) },
        { "maximum", Variant(3) },
        { "step", Variant(1) }
    });
    
    subGroup->addProperty<int>("int", 3)->setOptions({
        { "minimum", Variant(-3) },
        { "maximum", Variant(4) },
        { "step", Variant(1) }
    });
    
    subGroup->addProperty<long>("long", 4l)->setOptions({
        { "minimum", Variant(-4l) },
        { "maximum", Variant(5l) },
        { "step", Variant(1l) }
    });
    
    subGroup->addProperty<long long>("longlong", 5ll)->setOptions({
        { "minimum", Variant(-5ll) },
        { "maximum", Variant(6ll) },
        { "step", Variant(1ll) }
    });
    
    subGroup = group.addGroup("unsigned_integrals");
    
    subGroup->addProperty<unsigned char>("uchar", 0u)->setOptions({
        { "minimum", Variant(0u) },
        { "maximum", Variant(10u) },
        { "step", Variant(1u) }
    });
    
    subGroup->addProperty<unsigned short>("ushort", 0u)->setOptions({
        { "minimum", Variant(0u) },
        { "maximum", Variant(20u) },
        { "step", Variant(2u) }
    });
    
    subGroup->addProperty<unsigned int>("uint", 0u)->setOptions({
        { "minimum", Variant(0u) },
        { "maximum", Variant(30u) },
        { "step", Variant(3u) }
    });
    
    subGroup->addProperty<unsigned long>("ulong", 0ul)->setOptions({
        { "minimum", Variant(0ul) },
        { "maximum", Variant(40ul) },
        { "step", Variant(4ul) }
    });
    
    subGroup->addProperty<unsigned long long>("ulonglong", 0ull)->setOptions({
        { "minimum", Variant(0ull) },
        { "maximum", Variant(50ull) },
        { "step", Variant(5ull) }
    });
    
    subGroup = group.addGroup("string");
    
    auto * stringProperty = subGroup->addProperty<std::string>("std_string", "Hallo Welt!");
    
    subGroup->addProperty<bool>("choices", false)->valueChanged.connect([stringProperty] (bool b)
        {
            if (b)
            {
                Variant choices = Variant::fromValue<std::vector<std::string>>({ "blau", "rot", "grün" });
                stringProperty->setOption("choices", choices);
            }
            else
            {
                stringProperty->removeOption("choices");
            }
        });
        
    subGroup = group.addGroup("other"); 

    subGroup->addProperty<FilePath>("filePath", "")->setOptions({
        { "uniqueidentifier", Variant("filePath") }
    });
    
    subGroup->addProperty<Color>("color", Color(128, 128, 128));
    
    enum class MyEnum { One, Two, Three };
    subGroup->addProperty<MyEnum>("enum", MyEnum::One)->setStrings({
        { MyEnum::One, "One" },
        { MyEnum::Two, "Two" },
        { MyEnum::Three, "Three" }
    });

    PropertyBrowser browser;
    browser.setRoot(&group);
    browser.show();

    return a.exec();
}
