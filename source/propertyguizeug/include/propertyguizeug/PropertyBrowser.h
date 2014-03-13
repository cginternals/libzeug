
#pragma once

#include <QTreeView>

#include <propertyguizeug/propertyguizeug.h>

namespace reflectionzeug
{
    class PropertyGroup;
}

namespace propertyguizeug
{

class PropertyDelegate;
class PropertyEditorFactory;
class PropertyModel;
class PropertyPainter;

class PROPERTYGUIZEUG_API PropertyBrowser : public QTreeView
{
public:
    PropertyBrowser(QWidget * parent = nullptr);
    
    PropertyBrowser(reflectionzeug::PropertyGroup * root,
                    QWidget * parent = nullptr);
    
    PropertyBrowser(PropertyEditorFactory * editorFactory,
                    PropertyPainter * painter,
                    QWidget * parent = nullptr);
    
    PropertyBrowser(reflectionzeug::PropertyGroup * root,
                    PropertyEditorFactory * editorFactory,
                    PropertyPainter * painter,
                    QWidget * parent = nullptr);
    
    ~PropertyBrowser();
    
    void setRoot(reflectionzeug::PropertyGroup * root);

protected:
    void initView();
    
protected:    
    PropertyModel * m_model;
    PropertyDelegate * m_delegate;
    
};
    
} // namespace propertyguizeug
