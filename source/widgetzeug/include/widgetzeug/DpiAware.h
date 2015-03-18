#pragma once

#include <widgetzeug/widgetzeug_api.h>

#include <QtGlobal> // used for qreal

class QWidget;
class QWindow;


namespace widgetzeug
{

/** 
 * @brief Trait that allows retrieval of a widget's DPI scale inforamtion
 */
class WIDGETZEUG_API DpiAware
{
public:
    static QWindow * handle(const QWidget & widget);

    static qreal dpiBasedScale(const QWidget * widget);
    virtual qreal dpiBasedScale() const = 0;

    static qreal devicePixelRatio(const QWidget * widget);
    virtual qreal devicePixelRatio() const = 0;
};

} // namespace widgetzeug
