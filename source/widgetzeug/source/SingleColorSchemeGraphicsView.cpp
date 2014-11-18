#include <widgetzeug/SingleColorSchemeGraphicsView.h>

#include <cmath>

#include <QDebug>

#include <widgetzeug/ColorSchemeGraphicsItem.h>


namespace widgetzeug
{

SingleColorSchemeGraphicsView::SingleColorSchemeGraphicsView(QWidget * parent)
:   DpiAwareGraphicsView(new QGraphicsScene(), parent)
,   m_item(new ColorSchemeGraphicsItem(this))
{
    setFrameShape(QFrame::NoFrame);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setInteractive(false);
    
    QPalette palette = this->palette();
    setBackgroundBrush(QBrush(palette.color(QPalette::Window)));
    
    scene()->addItem(m_item);
    m_item->setRotation(-90.f);
    m_item->setDetailedTooltip(true);
    m_item->setPos(0.f, 
                   m_item->boundingRect().width());
    setFixedHeight(std::ceil(m_item->boundingRect().width()));
}

void SingleColorSchemeGraphicsView::setScheme(ColorScheme * scheme)
{
    m_item->setScheme(scheme);
    m_item->update();
}

ColorScheme * SingleColorSchemeGraphicsView::scheme()
{
    return m_item->scheme();
}

void SingleColorSchemeGraphicsView::setDeficiency(
    ColorScheme::ColorVisionDeficiency deficiency)
{
    m_item->setDeficiency(deficiency);
    m_item->update();
}

ColorScheme::ColorVisionDeficiency SingleColorSchemeGraphicsView::deficiency() const
{
    return m_item->deficiency();
}

void SingleColorSchemeGraphicsView::setClasses(int classes)
{
    m_item->setClasses(classes);
    scene()->setSceneRect(0.f, 0.f,
                          m_item->boundingRect().height(),
                          m_item->boundingRect().width());
    setFixedWidth(std::ceil(m_item->boundingRect().height()));
    m_item->update();
}

int SingleColorSchemeGraphicsView::classes() const
{
    return m_item->classes();
}

} // namespace widgetzeug
