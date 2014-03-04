
#pragma once

#include <iostream>
#include <utility>

namespace reflectionzeug
{

template <typename Type, class Object>
void AbstractPropertyVisitor::registerTypeHandler(
    void (Object::*visitMethod)(Property<Type> &),
    Object * object)
{
    addTypeHandler<Type>([object, visitMethod] (ValueProperty & property)
    {
        Property<Type> * specializedProperty = static_cast<Property<Type> *>(&property);
        (object->*visitMethod)(*specializedProperty);
    });
}

template <typename Type>
void AbstractPropertyVisitor::registerTypeHandler(const std::function<void(Property<Type> &)> & functor)
{
    addTypeHandler<Type>([functor] (ValueProperty & property)
    {
        Property<Type> * specializedProperty = static_cast<Property<Type> *>(&property);
        functor(*specializedProperty);
    });
}

template <typename Type>
void AbstractPropertyVisitor::addTypeHandler(const std::function<void(ValueProperty &)> & functor)
{
    const std::type_index type(typeid(Property<Type>));
    
    auto functorIt = m_functors.find(type);

    if (functorIt != m_functors.end())
        m_functors.erase(functorIt);

    m_functors.emplace(type, functor);
}
    
} // namespace reflectionzeug
