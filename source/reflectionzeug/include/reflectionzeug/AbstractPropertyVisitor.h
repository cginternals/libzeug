
#pragma once

#include <typeinfo>
#include <typeindex>
#include <functional>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{

template <typename Type>
class Property;
    
class Color;
class FilePath;
    
/** \brief Part of the Visitor Pattern implementation.
*/   
class REFLECTIONZEUG_API AbstractPropertyVisitor
{
public:
    AbstractPropertyVisitor();
    virtual ~AbstractPropertyVisitor() = default;
    
    void handle(ValueProperty & property);
    
    template <typename Type, class Object>
    void registerTypeHandler(void (Object::*visitMethod)(Property<Type> &),
                             Object * object);
    
    template <typename Type>
    void registerTypeHandler(const std::function<void(Property<Type> &)> & functor);

protected:
    virtual void visit(Property<bool> & property) = 0;
    virtual void visit(Property<int> & property) = 0;
    virtual void visit(Property<double> & property) = 0;
    virtual void visit(Property<std::string> & property) = 0;
    virtual void visit(Property<Color> & property) = 0;
    virtual void visit(Property<FilePath> & property) = 0;
    
    virtual void visit(Property<std::vector<bool>> & property) = 0;
    virtual void visit(Property<std::vector<int>> & property) = 0;
    virtual void visit(Property<std::vector<double>> & property) = 0;
    virtual void visit(Property<std::set<int>> & property) = 0;

private:
    template <typename Type>
    void addTypeHandler(const std::function<void(ValueProperty &)> & functor);

private:
    std::unordered_map<std::type_index, std::function<void(ValueProperty &)>> m_functors;

};

} // namespace reflectionzeug

#include "AbstractPropertyVisitor.hpp"
