
#pragma once

#include <QStyledItemDelegate>
#include <propertyzeug/Property.h>
#include <propertyzeug/AbstractPropertyVisitor.h>
#include "propertyguizeug.h"

namespace propertyguizeug {
    
using namespace propertyzeug;

class PropertyDelegate : public QStyledItemDelegate, public AbstractPropertyVisitor
{
    Q_OBJECT
    
public:
    PropertyDelegate(QWidget * parent = nullptr);
    virtual ~PropertyDelegate();
    
    virtual QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option,
                                   const QModelIndex & index) const;
    
    virtual void setEditorData(QWidget * editor, const QModelIndex & index) const;
    
    virtual void setModelData(QWidget * editor, QAbstractItemModel * model,
                              const QModelIndex & index) const;
    
    virtual void updateEditorGeometry(QWidget * editor,
                                      const QStyleOptionViewItem & option,
                                      const QModelIndex &index) const;
    
    virtual QSize sizeHint (const QStyleOptionViewItem & option,
                            const QModelIndex & index) const;

    virtual void visit(Property<bool> & property) {};
    virtual void visit(Property<int> & property);
    virtual void visit(Property<unsigned int> & property);
    virtual void visit(Property<long> & property);
    virtual void visit(Property<unsigned long> & property);
    virtual void visit(Property<char> & property);
    virtual void visit(Property<unsigned char> & property);
    virtual void visit(Property<float> & property) {};
    virtual void visit(Property<double> & property) {};
    virtual void visit(Property<std::string> & property);
    virtual void visit(Property<Color> & property);
    virtual void visit(Property<FilePath> & property) {};
    
    virtual void visit(Property<std::vector<bool>> & property) {};
    virtual void visit(Property<std::vector<int>> & property);
    virtual void visit(Property<std::vector<float>> & property) {};
    virtual void visit(Property<std::vector<double>> & property) {};

    virtual void visit(PropertyGroup & property) {};


protected:
    QWidget * createEditorForProperty(QWidget * parent, AbstractProperty * property);

    QWidget * m_activeEditor;
};
    
} // namespace 
