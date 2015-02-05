#pragma once

#include <QWidget>

#include <widgetzeug/widgetzeug_api.h>

class QFileSystemWatcher;

class Ui_DataLinkWidget;

namespace widgetzeug
{

class WIDGETZEUG_API DataLinkWidget : public QWidget
{
    Q_OBJECT

public:
    DataLinkWidget(QWidget * parent = nullptr);

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
    Ui_DataLinkWidget * m_ui;
    QFileSystemWatcher * m_watcher;
    bool m_watchFile;
};

} // namespace widgetzeug
