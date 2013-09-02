
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <propertyzeug/PropertyGroup.h>
#include <propertyguizeug/WidgetBuilder.h>

using namespace propertyzeug;
using namespace propertyguizeug;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    PropertyGroup group("group", "Group");
    WidgetBuilder builder;
    QWidget * widget = builder.build(group);
    widget->show();
    
    int result = a.exec();
    delete widget;
    
    return result;
}