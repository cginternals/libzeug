#include <reflectionzeug/PropertyGroup.h>
#include "BackendJavaScript/JSPropVisitor.h"


namespace scriptzeug
{


using namespace reflectionzeug;


JSPropVisitor::JSPropVisitor(Operation operation)
: m_operation(operation)
{
}

JSPropVisitor::~JSPropVisitor()
{
}

Variant & JSPropVisitor::value()
{
    return m_value;
}

void JSPropVisitor::setValue(const Variant & value)
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
    if (m_operation == GetOperation) {
        m_value = Variant::Array();
        const std::vector<bool> &arr = property.value();
        for (std::vector<bool>::const_iterator it = arr.begin(); it != arr.end(); ++it) {
            m_value.append(Variant(*it));
        }
    } else {
        std::vector<bool> arr;
        for (unsigned int i=0; i<m_value.size(); i++) {
            arr.push_back(m_value[i].toBool());
        }
        property.setValue(arr);
    }
}

void JSPropVisitor::visit(Property<std::vector<int>> & property)
{
    if (m_operation == GetOperation) {
        m_value = Variant::Array();
        const std::vector<int> &arr = property.value();
        for (std::vector<int>::const_iterator it = arr.begin(); it != arr.end(); ++it) {
            m_value.append(Variant(*it));
        }
    } else {
        std::vector<int> arr;
        for (unsigned int i=0; i<m_value.size(); i++) {
            arr.push_back(m_value[i].toInt());
        }
        property.setValue(arr);
    }
}

void JSPropVisitor::visit(Property<std::vector<double>> & property)
{
    if (m_operation == GetOperation) {
        m_value = Variant::Array();
        const std::vector<double> &arr = property.value();
        for (std::vector<double>::const_iterator it = arr.begin(); it != arr.end(); ++it) {
            m_value.append(Variant(*it));
        }
    } else {
        std::vector<double> arr;
        for (double i=0; i<m_value.size(); i++) {
            arr.push_back(m_value[i].toDouble());
        }
        property.setValue(arr);
    }
}

void JSPropVisitor::visit(Property<std::set<int>> & property)
{
    if (m_operation == GetOperation) {
        m_value = Variant::Array();
        const std::set<int> &set = property.value();
        for (std::set<int>::const_iterator it = set.begin(); it != set.end(); ++it) {
            m_value.append(Variant(*it));
        }
    } else {
        std::set<int> set;
        for (unsigned int i=0; i<m_value.size(); i++) {
            set.insert(m_value[i].toInt());
        }
        property.setValue(set);
    }
}


} // namespace scriptzeug
