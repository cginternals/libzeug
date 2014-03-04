
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/Property.h>

#include <reflectionzeug/AbstractPropertyVisitor.h>

namespace reflectionzeug
{

AbstractPropertyVisitor::AbstractPropertyVisitor()
{
    registerTypeHandler(&AbstractPropertyVisitor::visitBool, this);
    registerTypeHandler(&AbstractPropertyVisitor::visitInt, this);
    registerTypeHandler(&AbstractPropertyVisitor::visitDouble, this);
    registerTypeHandler(&AbstractPropertyVisitor::visitString, this);
    registerTypeHandler(&AbstractPropertyVisitor::visitColor, this);
    registerTypeHandler(&AbstractPropertyVisitor::visitFilePath, this);
    registerTypeHandler(&AbstractPropertyVisitor::visitBoolVector, this);
    registerTypeHandler(&AbstractPropertyVisitor::visitIntVector, this);
    registerTypeHandler(&AbstractPropertyVisitor::visitDoubleVector, this);
    registerTypeHandler(&AbstractPropertyVisitor::visitIntSet, this);
}

AbstractPropertyVisitor::~AbstractPropertyVisitor()
{
}
    
void AbstractPropertyVisitor::visit(ValueProperty & property)
{
    const std::type_index type(typeid(property));
    
    if (m_functors.count(type) == 0)
    {
        std::cout << "Could not visit not registered property." << std::endl;
        return;
    }
    
    m_functors.at(type)(property);
}

} // namespace reflectionzeug
