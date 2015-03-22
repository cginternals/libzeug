#pragma once

#include <memory>

#include <QWidget>

#include <widgetzeug/widgetzeug_api.h>


class QFileSystemWatcher;
class QCompleter;

class Ui_DataLinkWidget;


namespace widgetzeug
{

class WIDGETZEUG_API DataLinkWidget : public QWidget
{
    Q_OBJECT

public:
    DataLinkWidget(QWidget * parent = nullptr);
    virtual ~DataLinkWidget();

    void addFileName(const QString & fileName, bool active = false);
    void setFileName(const QString & fileName);
    QString fileName() const;

    QStringList fileNames() const;

    void setFileLinked(bool linked);
    bool fileLinked() const;

    void setFileIssue(bool enable);

    void setFilter(const QString & filter);

    void setReadOnly(bool enabled);
    bool readOnly() const;

    bool browse();
    void save();

signals:
    // ToDo: rename signals
    void fileChanged(const QString & fileName);
    void save(const QString & fileName);

protected slots:
    void on_fileNameComboBox_currentIndexChanged(const QString & text);
    void on_fileNameComboBox_editTextChanged(const QString & text);

    void on_browsePushButton_clicked(bool);
    void on_savePushButton_clicked(bool);

    void on_linkCheckBox_stateChanged(int state);

protected:
    bool isRecent(const QString & fileName) const;

    QCompleter * completer();

    void updateWatcher();

private:

    QString m_path; ///< path of the lastly typed fileName
    QString m_lastEmitedFileName;

    QFileSystemWatcher * m_watcher;
    bool m_watchFile;

    QString m_filter;

    std::unique_ptr<Ui_DataLinkWidget> m_ui;
};

} // namespace widgetzeug
