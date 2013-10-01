
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
    constraints.addProperty<std::vector<int>>("Position", std::vector<int>({ 10, 20, 30 }));
    settings.addProperty(&constraints);
    constraints.addProperty("Height", 3);
    constraints.addProperty("Width", 12.3);
    settings.addProperty<std::string>("FilePath", "/Users/Horst/Desktop/");
    settings.addProperty<std::vector<int>>("Mat3x2", {1,2,3,4,5,6});
    settings.property<std::vector<int>>("Mat3x2")->setDimensions(2,3);
    settings.addProperty<std::vector<double>>("Mat2x2", {1.1, 2.3, 6.1, 4});
    settings.property<std::vector<double>>("Mat2x2")->setDimensions(2,2);
    settings.addProperty<bool>("Activate", true);
    settings.addProperty<int>("Count", 79);
    PropertyGroup extras("Extras");
    settings.addProperty(&extras);
    extras.addProperty<Color>("Color", Color(255,122,0,190));
    extras.addProperty<FilePath>("Path", FilePath("/Users/max/"));
    extras.property<FilePath>("Path")->setIsFile(false);
    extras.addProperty<std::string>("Animal", "Rabbit");
    extras.property<std::string>("Animal")->setChoices({"Rabbit", "Duck", "Elephant"});
    PropertyGroup general("General");
    extras.addProperty(&general);
    general.addProperty<std::vector<bool>>("BoolMat", {true, false, true, false});
    general.property<std::vector<bool>>("BoolMat")->setDimensions(2,2);

    PropertyBrowser browser1(&settings);
    browser1.show();
    
    PropertyBrowser browser2(&settings);
    browser2.show();
    
    return a.exec();
}
