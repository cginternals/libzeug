
#pragma once

#include <QTableView>
#include <QHeaderView>
#include "VectorModel.h"
#include "VectorDelegate.h"

namespace propertyguizeug {

using namespace propertyzeug;

template <typename Type>
class VectorEditor : public QTableView
{
public:
    VectorEditor(Property<std::vector<Type>> * property, QWidget * parent = nullptr);
    virtual ~VectorEditor();

protected:
    VectorModel<Type> * m_model;
    VectorDelegate<Type> * m_delegate;

};

template <typename Type>
VectorEditor<Type>::VectorEditor(Property<std::vector<Type>> * property, QWidget * parent)
:   QTableView(parent)
,   m_model(new VectorModel<Type>(property, this))
,   m_delegate(new VectorDelegate<Type>(property, this))
{
    this->setModel(m_model);
    this->setItemDelegate(m_delegate);
    this->verticalHeader()->hide();
    this->horizontalHeader()->hide();
}

template <typename Type>
VectorEditor<Type>::~VectorEditor()
{
}

} // namespace
