
#include <iostream>
#include <QApplication>
#include <QTreeView>
#include <QWidget>
#include <QDebug>
#include <propertyzeug/PropertyGroup.h>
#include <propertyguizeug/WidgetBuilder.h>
#include <propertyguizeug/PropertyItemModel.h>

using namespace propertyzeug;
using namespace propertyguizeug;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    PropertyGroup settings("Settings");
    PropertyGroup constraints("Constraints");
    constraints.addProperty<std::vector<int>>("Position", std::vector<int>(100, 200));
    settings.addProperty(&constraints);
    constraints.addProperty("prop3", 3);
    
    QTreeView treeView;
    PropertyItemModel model(&settings);
    treeView.setModel(&model);
    treeView.show();
    
    return a.exec();
}