
#pragma once

#include <reflectionzeug/AbstractPropertyVisitor.h>

#include <propertyguizeug/propertyguizeug.h>


class QWidget;
namespace reflectionzeug
{
    template <typename Type>
    class Property;
    class ValueProperty;
    class Color;
    class FilePath;
}


namespace propertyguizeug
{
    
class PROPERTYGUIZEUG_API PropertyEditorFactory : public reflectionzeug::AbstractPropertyVisitor
{
public:
    PropertyEditorFactory();
    virtual ~PropertyEditorFactory();

    QWidget * createEditor(reflectionzeug::ValueProperty & property);
    QWidget * createEditorWithParent(reflectionzeug::ValueProperty & property, QWidget * parent);

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
    QWidget * m_editor;
};

} // namespace propertyguizeug
