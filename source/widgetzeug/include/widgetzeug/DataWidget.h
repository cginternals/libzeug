#pragma once

#include <QWidget>

#include <widgetzeug/widgetzeug_api.h>

class QFileSystemWatcher;

class Ui_DataWidget;

namespace widgetzeug
{

class WIDGETZEUG_API DataWidget : public QWidget
{
    Q_OBJECT

public:
    DataWidget(QWidget * parent = nullptr);

signals:
    void fileChanged(const QString & fileName);
    void exportPressed(const QString & fileName);

protected:
    void onButtonPressed();
    void onComboBoxCurrentIndexChanged(int index);
    void onCheckBoxChanged(int state);
    
private:
    bool fileNameExists(const QString & fileName);
    void updateWatcher();

private:
    Ui_DataWidget * m_ui;
    QFileSystemWatcher * m_watcher;
    bool m_watchFile;
};

} // namespace widgetzeug
