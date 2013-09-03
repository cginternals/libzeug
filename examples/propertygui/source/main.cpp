
#include <iostream>
#include <QApplication>
#include <QTreeView>
#include <QWidget>
#include <QDebug>
#include <QStandardItemModel>
#include <propertyzeug/PropertyGroup.h>
#include <propertyguizeug/WidgetBuilder.h>
#include <propertyguizeug/PropertyItemModel.h>

using namespace propertyzeug;
using namespace propertyguizeug;

int depth = 0;

void put(QAbstractItemModel & model, const QModelIndex & index)
{
    std::cout << ">>>>>>>>> Depth: " << depth << std::endl;
    qDebug() << "ModelIndex: " << index;
    qDebug() << "Parent: " << model.parent(index);
//    std::cout << "ModelIndex: " << index.column() << ", " << index.row() << std::endl;
    std::cout << "ColumnCount: ";
    std::cout << model.columnCount(index) << " | ";
    std::cout << "RowCount: " << model.rowCount(index) << std::endl;
    std::cout << "Data: " << model.data(index).toString().toStdString() << std::endl;
    for (int i = 0; i < model.rowCount(index); i++) {
        depth++;
        QModelIndex childIndex = model.index(i, 0, index);
        put(model, childIndex);
        depth--;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    PropertyGroup group("root");
    group.addProperty("prop1", 4);
    
    PropertyGroup group2("prop2");
    group.addProperty(&group2);
    group2.addProperty("prop3", 3);
    
    QStandardItemModel stdmodel;
    QStandardItem root(QString("root"));
    QStandardItem item1(QString("prop1"));
    QStandardItem item2(QString("prop2"));
    QStandardItem item3(QString("prop3"));
    stdmodel.setItem(0, 0, &root);
    root.setChild(0, 0, &item1);
    root.setChild(1, 0, &item2);
    item2.setChild(0, 0, &item3);
    
    QTreeView treeView;
    PropertyItemModel model(&group);
    treeView.setModel(&model);
    treeView.show();
    put(stdmodel, QModelIndex());
    std::cout << "<<<<<<<<<<<<<<<<<" << std::endl;
    put(model, QModelIndex());
    

    
    return a.exec();
}