#pragma once

#include <QDockWidget>

#include <widgetzeug/widgetzeug_api.h>


class QScrollArea;
class QVBoxLayout;


namespace widgetzeug
{

/** @brief Vertically aligns multiple widgets into a dockable scrollarea.
 *
 * The DockWidget is designed as follows:
 *
 * - QDockWidget with QScrollArea as (central) widget
 *  - An additional QWidget inside the QScrollArea
 *   - A QVBoxLayout assigned to that QWidget
 *     - Multiple widgets within the QVBoxLayout, added by addWidget(), 
 *       each inserted wrapped by a QGroupBox
 *   - A stretch as last item of the VBoxLayout
 *
 * Note: do not use setWidget() and widget() of QDockWidget's interface, 
 * but instead use addWidget to insert widgets into this dockable widget.
 *
 * Example for using a DockableScrollAreaWidget:
 * \code{.cpp}
 *  auto dockWidget = new DockableScrollAreaWidget(QObject::tr("Color Scheme Presets"));
 *
 *  dockWidget->addWidget(new DataLinkWidget());
 *  dockWidget->addWidget(new ColorSchemePresets("data/colorbrewer.json"));
 *
 *  dockWidget->show();
 * \endcode
 * }
 */
class WIDGETZEUG_API DockableScrollAreaWidget : public QDockWidget
{
    Q_OBJECT

public:

    //@{
    /** @brief Constructor. Sets up the above mentioned layout.
     */
    DockableScrollAreaWidget(const QString & title, QWidget * parent = nullptr, Qt::WindowFlags flags = 0);
    DockableScrollAreaWidget(QWidget * parent = nullptr, Qt::WindowFlags flags = 0);
    //@}

    /** @brief Appends the widget to the bottom of this dockable scroll area widget.
      *
      * Appends the widget to the vertical layout of this dock widget, thereby wrapping the 
      * widget inside a QGroupWidget and using the widgets window title as the groupbox's title.
      */
    void addWidget(QWidget * widget, int stretch = 0);

protected:

    //@{
    /** @brief Handle, easing the access (no need for cast...)
      */
    QScrollArea * m_scrollArea;
    QVBoxLayout * m_vbox;
    //@}
};

} // namespace widgetzeug
