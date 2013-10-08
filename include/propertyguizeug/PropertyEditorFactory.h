
#pragma once

#include <propertyzeug/AbstractPropertyVisitor.h>

#include <propertyguizeug/propertyguizeug.h>


class QWidget;

namespace zeug {

template <typename Type>
class Property;
class ValuePropertyBase;
class PropertyGroup;

class Color;
class FilePath;
    
class PROPERTYGUIZEUG_API PropertyEditorFactory : public AbstractPropertyVisitor
{
public:
    PropertyEditorFactory();
    virtual ~PropertyEditorFactory();

    QWidget * createEditor(ValuePropertyBase & property);

    virtual void visit(Property<bool> & property);
    virtual void visit(Property<int> & property);
    virtual void visit(Property<double> & property);
    virtual void visit(Property<std::string> & property);
    virtual void visit(Property<Color> & property);
    virtual void visit(Property<FilePath> & property);
    
    virtual void visit(Property<std::vector<bool>> & property);
    virtual void visit(Property<std::vector<int>> & property);
    virtual void visit(Property<std::vector<double>> & property);
    
protected:
    QWidget * m_editor;
};

} // namespace zeug
