
#pragma once

#include <QTreeView>

#include <propertyguizeug/propertyguizeug_api.h>

namespace reflectionzeug
{
    class PropertyGroup;
}

namespace propertyguizeug
{

class PropertyDelegate;
class PropertyEditorFactory;
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
    PropertyDelegate * m_delegate;
    
};
    
} // namespace propertyguizeug
