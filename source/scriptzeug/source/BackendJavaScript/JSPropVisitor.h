#pragma once


#include <reflectionzeug/AbstractPropertyVisitor.h>
#include "scriptzeug/Variant.h"


namespace scriptzeug
{


/** \brief Helper class for setting and getting properties
 */
class JSPropVisitor : public reflectionzeug::AbstractPropertyVisitor
{
public:
    enum Operation {
        GetOperation,
        SetOperation
    };

public:
    JSPropVisitor(Operation operation);
    virtual ~JSPropVisitor();

    Variant & value();
    void setValue(const Variant & value);
    virtual void visit(reflectionzeug::Property<bool> & property);
    virtual void visit(reflectionzeug::Property<int> & property);
    virtual void visit(reflectionzeug::Property<double> & property);
    virtual void visit(reflectionzeug::Property<std::string> & property);
    virtual void visit(reflectionzeug::Property<reflectionzeug::Color> & property);
    virtual void visit(reflectionzeug::Property<reflectionzeug::FilePath> & property);
    virtual void visit(reflectionzeug::Property<std::vector<bool>> & property);
    virtual void visit(reflectionzeug::Property<std::vector<int>> & property);
    virtual void visit(reflectionzeug::Property<std::vector<double>> & property);
    virtual void visit(reflectionzeug::Property<std::set<int>> & property);

protected:
    Operation m_operation;
    Variant   m_value;
};


} // namespace scriptzeug
