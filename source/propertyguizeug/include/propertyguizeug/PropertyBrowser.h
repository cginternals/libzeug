#pragma once

#include <QTreeView>

#include <propertyguizeug/propertyguizeug_api.h>

namespace reflectionzeug
{
    class PropertyGroup;
}

namespace propertyguizeug
{

class AbstractPropertyEditorPlugin;
class AbstractPropertyPainterPlugin;
class PropertyDelegate;

class PROPERTYGUIZEUG_API PropertyBrowser : public QTreeView
{
    Q_OBJECT

public:
    PropertyBrowser(QWidget * parent = nullptr);
    
    PropertyBrowser(reflectionzeug::PropertyGroup * root,
                    QWidget * parent = nullptr);
    
    ~PropertyBrowser();
    
    void setRoot(reflectionzeug::PropertyGroup * root);
    void setAlwaysExpandGroups(bool b);
    
    void addEditorPlugin(AbstractPropertyEditorPlugin * plugin);
    void addPainterPlugin(AbstractPropertyPainterPlugin * plugin);

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
