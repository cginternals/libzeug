
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
class AbstractPropertyEditorPlugin;
class PropertyPainter;

class PROPERTYGUIZEUG_API PropertyBrowser : public QTreeView
{
    Q_OBJECT

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
    void setAlwaysExpandGroups(bool b);

    void addPlugin(AbstractPropertyEditorPlugin * plugin);

protected slots:
    void onRowsInserted(const QModelIndex & parentIndex, int first, int last);

private:
    void initView();
    void expandAllGroups();
    
private:    
    PropertyDelegate * m_delegate;
    bool m_alwaysExpandGroups;
};
    
} // namespace propertyguizeug
