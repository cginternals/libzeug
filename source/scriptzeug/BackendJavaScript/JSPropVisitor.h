#pragma once


#include <propertyzeug/AbstractPropertyVisitor.h>
#include "scriptzeug/Value.h"


namespace scriptzeug
{


/** \brief Helper class for setting and getting properties
 */
class JSPropVisitor : public zeug::AbstractPropertyVisitor
{
public:
    enum Operation {
        GetOperation,
        SetOperation
    };

public:
    JSPropVisitor(Operation operation);
    virtual ~JSPropVisitor();

    scriptzeug::Value & value();
    void setValue(const scriptzeug::Value & value);
    virtual void visit(zeug::Property<bool> & property);
    virtual void visit(zeug::Property<int> & property);
    virtual void visit(zeug::Property<double> & property);
    virtual void visit(zeug::Property<std::string> & property);
    virtual void visit(zeug::Property<zeug::Color> & property);
    virtual void visit(zeug::Property<zeug::FilePath> & property);
    virtual void visit(zeug::Property<std::vector<bool>> & property);
    virtual void visit(zeug::Property<std::vector<int>> & property);
    virtual void visit(zeug::Property<std::vector<double>> & property);
    virtual void visit(zeug::Property<std::set<int>> & property);

protected:
    Operation         m_operation;
    scriptzeug::Value m_value;
};


} // namespace
