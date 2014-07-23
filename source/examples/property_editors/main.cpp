
#include <string>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <propertyguizeug/PropertyBrowser.h>


using namespace reflectionzeug;
using namespace propertyguizeug;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("hpicgs_libzeug");
    
    PropertyGroup group;
    
    PropertyGroup * subGroup;
    
    subGroup = group.addGroup("floating_point");
    
    subGroup->addProperty<float>("float", 2.0f)->setOptions({
        { "minimum", Variant2(1.2f) },
        { "maximum", Variant2(13.0f) },
        { "step", Variant2(0.5f) },
        { "precision", Variant2(1u) }
    });
    
    subGroup->addProperty<double>("double", 0.0)->setOptions({
        { "minimum", Variant2(-1.0) },
        { "maximum", Variant2(1.0) },
        { "step", Variant2(0.01) },
        { "precision", Variant2(2u) }
    });
    
    subGroup = group.addGroup("signed_integrals");
    
    subGroup->addProperty<char>("char", 1)->setOptions({
        { "minimum", Variant2(-1) },
        { "maximum", Variant2(2) },
        { "step", Variant2(1) }
    });
    
    subGroup->addProperty<short>("short", 2)->setOptions({
        { "minimum", Variant2(-2) },
        { "maximum", Variant2(3) },
        { "step", Variant2(1) }
    });
    
    subGroup->addProperty<int>("int", 3)->setOptions({
        { "minimum", Variant2(-3) },
        { "maximum", Variant2(4) },
        { "step", Variant2(1) }
    });
    
    subGroup->addProperty<long>("long", 4l)->setOptions({
        { "minimum", Variant2(-4l) },
        { "maximum", Variant2(5l) },
        { "step", Variant2(1l) }
    });
    
    subGroup->addProperty<long long>("longlong", 5ll)->setOptions({
        { "minimum", Variant2(-5ll) },
        { "maximum", Variant2(6ll) },
        { "step", Variant2(1ll) }
    });
    
    subGroup = group.addGroup("unsigned_integrals");
    
    subGroup->addProperty<unsigned char>("uchar", 0u)->setOptions({
        { "minimum", Variant2(0u) },
        { "maximum", Variant2(10u) },
        { "step", Variant2(1u) }
    });
    
    subGroup->addProperty<unsigned short>("ushort", 0u)->setOptions({
        { "minimum", Variant2(0u) },
        { "maximum", Variant2(20u) },
        { "step", Variant2(2u) }
    });
    
    subGroup->addProperty<unsigned int>("uint", 0u)->setOptions({
        { "minimum", Variant2(0u) },
        { "maximum", Variant2(30u) },
        { "step", Variant2(3u) }
    });
    
    subGroup->addProperty<unsigned long>("ulong", 0ul)->setOptions({
        { "minimum", Variant2(0ul) },
        { "maximum", Variant2(40ul) },
        { "step", Variant2(4ul) }
    });
    
    subGroup->addProperty<unsigned long long>("ulonglong", 0ull)->setOptions({
        { "minimum", Variant2(0ull) },
        { "maximum", Variant2(50ull) },
        { "step", Variant2(5ull) }
    });
    
    group.addProperty<bool>("readonly", false)->valueChanged.connect([&group] (bool b) 
        {
            if (b)
                group.addFlag("readonly");
            else
                group.removeFlag("readonly");
        });
        
    group.addProperty<bool>("disabled", false)->valueChanged.connect([&group] (bool b)
        {
            if (b)
                group.addFlag("disabled");
            else
                group.removeFlag("disabled");
        });

    PropertyBrowser browser;
    browser.setRoot(&group);
    browser.show();

    return a.exec();
}
