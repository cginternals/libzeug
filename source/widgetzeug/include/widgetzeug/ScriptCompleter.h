#pragma once

#include <QCompleter>

#include <widgetzeug/widgetzeug_api.h>

class QStandardItemModel;
class QString;
class QStringList;

namespace widgetzeug
{

/** \brief ToDo
*
* ToDo
*/
class WIDGETZEUG_API ScriptCompleter : public QCompleter
{
public:
    ScriptCompleter();
    virtual ~ScriptCompleter();

    void registerWord(const QString & word);
    void deregisterWord(const QString & word);

    void registerWords(const QStringList & words);
    void deregisterWords(const QStringList & words);

protected:
    QStandardItemModel * m_model;
};

} // namespace widgetzeug
