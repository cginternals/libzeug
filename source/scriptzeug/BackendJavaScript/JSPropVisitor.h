#pragma once


#include <propertyzeug/AbstractPropertyVisitor.h>
#include "scriptzeug/Variant.h"


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

    Variant & value();
    void setValue(const Variant & value);
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
    Operation m_operation;
    Variant   m_value;
};


} // namespace
