
#include <iostream>
#include <QApplication>
#include <QTreeView>
#include <QWidget>
#include <QDebug>
#include <propertyzeug/Property.h>
#include <propertyzeug/PropertyGroup.h>
#include <propertyguizeug/PropertyItemModel.h>
#include <propertyguizeug/PropertyDelegate.h>

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

    QTreeView treeView;
    treeView.setAlternatingRowColors(true);
    PropertyItemModel model(&settings);
    PropertyDelegate delegate;
    treeView.setModel(&model);
    treeView.setItemDelegateForColumn(1, &delegate);
    treeView.show();
    treeView.expandAll();
    
    return a.exec();
}
