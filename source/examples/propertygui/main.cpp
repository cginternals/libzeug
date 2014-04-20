
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/PropertySerializer.h>
#include <reflectionzeug/PropertyDeserializer.h>
#include <propertyguizeug/PropertyBrowser.h>

#include "Switch.h"

#ifdef WIN32
#define SETTINGS_PATH ".\\data\\propertygui.ini"
#else
#define SETTINGS_PATH "./data/propertygui.ini"
#endif


using namespace reflectionzeug;
using namespace propertyguizeug;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("hpicgs_libzeug");
    
    auto * settings = new PropertyGroup("settings");
    auto * size = settings->addGroup("size");
    size->addProperty<int>("width", 11);
    settings->addProperty<bool>("bool", true);
    settings->addProperty<std::array<std::string, 3>>("string_array", std::array<std::string, 3>{ "hu", "hu", "hu"});

    
    auto * browser = new PropertyBrowser(settings);
    browser->show();

    int result = a.exec();

    delete settings;
    delete browser;
    
    return result;
}
