
#include <iostream>
#include <QApplication>
#include <propertyzeug/Property.h>
#include <propertyzeug/PropertyGroup.h>
#include <propertyguizeug/PropertyBrowser.h>

using namespace propertyzeug;
using namespace propertyguizeug;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    PropertyGroup settings("Settings");
    PropertyGroup constraints("Constraints");
    constraints.addProperty<std::vector<int>>("Position", std::vector<int>({ 100, 200 }));
    settings.addProperty(&constraints);
    constraints.addProperty("Height", 3);
    constraints.addProperty("Width", 12);
    settings.addProperty<std::string>("FilePath", "/Users/Horst/Desktop/");
    settings.addProperty<std::vector<int>>("Mat3x2", {1,2,3,4,5,6});
    settings.property<std::vector<int>>("Mat3x2")->setDimensions(3,2);
    settings.addProperty<bool>("Activate", true);
    settings.addProperty<int>("Count", 79);
    PropertyGroup extras("Extras");
    settings.addProperty(&extras);
    extras.addProperty<Color>("Color", Color(127,127,127));
    extras.addProperty<FilePath>("Path", FilePath("/Users/max/"));
    extras.addProperty<std::string>("Animal", "Rabbit");
    extras.property<std::string>("Animal")->setChoices({"Rabbit", "Duck", "Elephant"});

    PropertyBrowser browser(&settings);
    browser.show();
    
    return a.exec();
}
