#pragma once

#include <reflectionzeug/property_declaration.h>
#include <reflectionzeug/StandardPropertyVisitor.h>

#include <propertyguizeug/propertyguizeug_api.h>

class QWidget;

namespace propertyguizeug
{
    
class PROPERTYGUIZEUG_API PropertyEditorFactory : public reflectionzeug::StandardPropertyVisitor
{
public:
    PropertyEditorFactory();

    QWidget * createEditor(reflectionzeug::AbstractValueProperty & property);
    QWidget * createEditorWithParent(reflectionzeug::AbstractValueProperty & property, QWidget * parent);

    virtual void visit(reflectionzeug::Property<bool> * property);
    virtual void visit(reflectionzeug::Property<reflectionzeug::FilePath> * property);

    virtual void visit(reflectionzeug::AbstractValueProperty * property);
    virtual void visit(reflectionzeug::ColorPropertyInterface * property);
    virtual void visit(reflectionzeug::EnumPropertyInterface * property);
    virtual void visit(reflectionzeug::UnsignedIntegralPropertyInterface * property);
    virtual void visit(reflectionzeug::SignedIntegralPropertyInterface * property);
    virtual void visit(reflectionzeug::FloatingPointPropertyInterface * property);
    virtual void visit(reflectionzeug::StringPropertyInterface * property);

protected:
    QWidget * m_editor;
};

} // namespace propertyguizeug
