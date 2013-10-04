
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <propertyzeug/AbstractPropertyVisitor.h>

class QWidget;

namespace zeug {

template <typename Type>
class Property;
class AbstractProperty;
class PropertyGroup;

class Color;
class FilePath;
    
class PROPERTYGUIZEUG_API PropertyEditorFactory : public AbstractPropertyVisitor
{
public:
    PropertyEditorFactory();
    virtual ~PropertyEditorFactory();

    QWidget * createEditor(AbstractProperty & property);

    virtual void visit(Property<bool> & property);
    virtual void visit(Property<int> & property);
    virtual void visit(Property<double> & property);
    virtual void visit(Property<std::string> & property);
    virtual void visit(Property<Color> & property);
    virtual void visit(Property<FilePath> & property);
    
    virtual void visit(Property<std::vector<bool>> & property);
    virtual void visit(Property<std::vector<int>> & property);
    virtual void visit(Property<std::vector<double>> & property);

    virtual void visit(PropertyGroup & property);
    
protected:
    QWidget * m_editor;
};

} // namespace
