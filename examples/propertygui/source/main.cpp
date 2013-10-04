
#include <iostream>
#include <QApplication>
#include <propertyzeug/Property.h>
#include <propertyzeug/PropertyGroup.h>
#include <propertyguizeug/PropertyBrowser.h>

using namespace zeug;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    PropertyGroup settings("Settings");
    PropertyGroup constraints("Constraints");
    
    int position[] = {10, 20, 30};
    int mat3x2[] = {1, 2, 3, 4, 5, 6};
    double mat2x2[] = {1.1, 2.3, 6.1, 4};
    bool boolMat[] = {true, false, true, false};

    constraints.addProperty<std::vector<int>>("Position", std::vector<int>(std::begin(position),
                                                                           std::end(position)));
    settings.addProperty(&constraints);
    constraints.addProperty("Height", 3);
    constraints.addProperty("Width", 12.3);
    settings.addProperty<std::string>("FilePath", "/Users/Horst/Desktop/");
    settings.addProperty<std::vector<int>>("Mat3x2", std::vector<int>(std::begin(mat3x2),
                                                                      std::end(mat3x2)));
    settings.property<std::vector<int>>("Mat3x2")->setDimensions(2,3);
    settings.addProperty<std::vector<double>>("Mat2x2", std::vector<double>(std::begin(mat2x2),
                                                                            std::end(mat2x2)));
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
    general.addProperty<std::vector<bool>>("BoolMat", std::vector<bool>(std::begin(boolMat),
                                                                        std::end(boolMat)));
    general.property<std::vector<bool>>("BoolMat")->setDimensions(2,2);

    PropertyBrowser browser1(&settings);
    browser1.show();
    
    return a.exec();
}
