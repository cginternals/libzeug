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

    QString linkedFileName() const;
    bool linkedFileExists() const;

    bool browse();
    void save();

signals:
    // ToDo: rename signals
    void fileChanged(const QString & fileName);
    void save(const QString & fileName);

protected slots:
    void on_dataComboBox_currentIndexChanged(int index);

    void on_browsePushButton_clicked(bool);
    void on_savePushButton_clicked(bool);

    void on_linkCheckBox_stateChanged(int state);

private:
    bool isRecent(const QString & fileName);
    void updateWatcher();

private:
    Ui_DataLinkWidget * m_ui;

    QFileSystemWatcher * m_watcher;
    bool m_watchFile;
};

} // namespace widgetzeug
