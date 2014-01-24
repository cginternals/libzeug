#include <propertyzeug/PropertyGroup.h>
#include "BackendJavaScript/JSPropVisitor.h"


namespace scriptzeug
{


using namespace zeug;


JSPropVisitor::JSPropVisitor(Operation operation)
: m_operation(operation)
{
}

JSPropVisitor::~JSPropVisitor()
{
}

scriptzeug::Value & JSPropVisitor::value()
{
    return m_value;
}

void JSPropVisitor::setValue(const scriptzeug::Value & value)
{
    m_value = value;
}

void JSPropVisitor::visit(Property<bool> & property)
{
    if (m_operation == GetOperation)
        m_value = property.value();
    else
        property.setValue(m_value.toBool());
}

void JSPropVisitor::visit(Property<int> & property)
{
    if (m_operation == GetOperation)
        m_value = property.value();
    else
        property.setValue(m_value.toInt());
}

void JSPropVisitor::visit(Property<double> & property)
{
    if (m_operation == GetOperation)
        m_value = property.value();
    else
        property.setValue(m_value.toDouble());
}

void JSPropVisitor::visit(Property<std::string> & property)
{
    if (m_operation == GetOperation)
        m_value = property.value();
    else
        property.setValue(m_value.toString());
}

void JSPropVisitor::visit(Property<Color> & property)
{
    // [TODO]
}

void JSPropVisitor::visit(Property<FilePath> & property)
{
    if (m_operation == GetOperation)
        m_value = property.value().string();
    else
        property.setValue(m_value.toString());
}

void JSPropVisitor::visit(Property<std::vector<bool>> & property)
{
    // [TODO]
}

void JSPropVisitor::visit(Property<std::vector<int>> & property)
{
    // [TODO]
}

void JSPropVisitor::visit(Property<std::vector<double>> & property)
{
    // [TODO]
}

void JSPropVisitor::visit(Property<std::set<int>> & property)
{
    // [TODO]
}


} // namespace
