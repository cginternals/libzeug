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
    void fileChanged(const QString & path);

protected:
    void onButtonPressed();
    void onComboBoxCurrentIndexChanged(int index);

private:
    Ui_DataWidget * m_ui;
    QFileSystemWatcher * m_watcher;
};

} // namespace widgetzeug
