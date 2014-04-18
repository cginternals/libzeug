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
    virtual void visit(reflectionzeug::Property<bool> * property) override;
    //virtual void visit(reflectionzeug::Property<int> * property) override;
    //virtual void visit(reflectionzeug::Property<double> * property) override;
    virtual void visit(reflectionzeug::Property<std::string> * property) override;
    virtual void visit(reflectionzeug::Property<reflectionzeug::Color> * property) override;
    virtual void visit(reflectionzeug::Property<reflectionzeug::FilePath> * property) override;
    //virtual void visit(reflectionzeug::Property<std::vector<bool>> * property) override;
    //virtual void visit(reflectionzeug::Property<std::vector<int>> * property) override;
    //virtual void visit(reflectionzeug::Property<std::vector<double>> * property) override;

    virtual void visit(reflectionzeug::SignedIntegralPropertyInterface * propertyInterface) override;
    virtual void visit(reflectionzeug::UnsignedIntegralPropertyInterface * propertyInterface) override;
    virtual void visit(reflectionzeug::FloatingPointPropertyInterface * propertyInterface) override;

virtual void visit(reflectionzeug::AbstractValueProperty * property) override {}
virtual void visit(reflectionzeug::EnumPropertyInterface * property) override {}

protected:
    Operation               m_operation;
    reflectionzeug::Variant m_value;
};


} // namespace scriptzeug
