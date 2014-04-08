
#pragma once

#include <reflectionzeug/property_declaration.h>
#include <reflectionzeug/StandardPropertyVisitor.h>

#include <propertyguizeug/propertyguizeug.h>

class QWidget;

namespace reflectionzeug
{
    class ValuePropertyInterface;
    class Color;
    class FilePath;
}

namespace propertyguizeug
{
    
class PROPERTYGUIZEUG_API PropertyEditorFactory : public reflectionzeug::StandardPropertyVisitor
{
public:
    PropertyEditorFactory();
    virtual ~PropertyEditorFactory();

    QWidget * createEditor(reflectionzeug::ValuePropertyInterface & property);
    QWidget * createEditorWithParent(reflectionzeug::ValuePropertyInterface & property, QWidget * parent);

    virtual void visit(reflectionzeug::Property<bool> * property);
    virtual void visit(reflectionzeug::Property<int> * property);
    virtual void visit(reflectionzeug::Property<double> * property);
    virtual void visit(reflectionzeug::Property<std::string> * property);
    virtual void visit(reflectionzeug::Property<reflectionzeug::Color> * property);
    virtual void visit(reflectionzeug::Property<reflectionzeug::FilePath> * property);

    virtual void visit(reflectionzeug::ValuePropertyInterface * property);
    virtual void visit(reflectionzeug::EnumPropertyInterface * property);

protected:
    QWidget * m_editor;
};

} // namespace propertyguizeug
