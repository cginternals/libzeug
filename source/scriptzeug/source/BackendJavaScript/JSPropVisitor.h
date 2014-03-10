#pragma once


#include <reflectionzeug/StandardPropertyVisitor.h>
#include <reflectionzeug/Variant.h>
#include "scriptzeug/scriptzeug.h"


namespace scriptzeug
{


/** \brief Helper class for setting and getting properties
 */
class JSPropVisitor : public reflectionzeug::StandardPropertyVisitor
{
public:
    enum Operation {
        GetOperation,
        SetOperation
    };

public:
    JSPropVisitor(Operation operation);
    virtual ~JSPropVisitor();

    reflectionzeug::Variant & value();
    void setValue(const reflectionzeug::Variant & value);
    virtual void visit(reflectionzeug::Property<bool> & property);
    virtual void visit(reflectionzeug::Property<int> & property);
    virtual void visit(reflectionzeug::Property<double> & property);
    virtual void visit(reflectionzeug::Property<std::string> & property);
    virtual void visit(reflectionzeug::Property<reflectionzeug::Color> & property);
    virtual void visit(reflectionzeug::Property<reflectionzeug::FilePath> & property);
    virtual void visit(reflectionzeug::Property<std::vector<bool>> & property);
    virtual void visit(reflectionzeug::Property<std::vector<int>> & property);
    virtual void visit(reflectionzeug::Property<std::vector<double>> & property);

protected:
    Operation               m_operation;
    reflectionzeug::Variant m_value;
};


} // namespace scriptzeug
