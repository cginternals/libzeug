#include <widgetzeug/ColorGradientWidget.h>

#include <QGraphicsLineItem>
#include <QResizeEvent>

namespace widgetzeug
{
    
class ColorGradientWidget::Scene : public QGraphicsScene
{
public:
    Scene(const ColorGradient & gradient, ColorGradientWidget * widget);
    
    void resize();
    
    void drawBackground(QPainter * painter, const QRectF & rect) override;
    
private:
    ColorGradientWidget & m_widget;
    ColorGradient m_gradient;
    
    QGraphicsLineItem * m_lineItem;
};
    
ColorGradientWidget::Scene::Scene(
    const ColorGradient & gradient,
    ColorGradientWidget * widget)
:   QGraphicsScene{widget}
,   m_widget{*widget}
,   m_gradient(gradient)
{
    setSceneRect(0.0, 0.0, 1.0, 1.0);
    m_lineItem = new QGraphicsLineItem{QLineF{0.5, 0.0, 0.5, 1.0}};
    m_lineItem->setCursor(Qt::SplitHCursor);
    addItem(m_lineItem);
}

void ColorGradientWidget::Scene::drawBackground(
    QPainter * painter,
    const QRectF & rect)
{
    auto gradientImage = m_gradient.image(m_widget.width());
    painter->drawImage(rect, gradientImage);
}

void ColorGradientWidget::Scene::resize()
{
    auto pen = QPen{};
    pen.setWidthF(1.0 / m_widget.width());
    pen.setColor(Qt::white);
    m_lineItem->setPen(pen);
}

ColorGradientWidget::ColorGradientWidget(
    const ColorGradient & gradient,
    QWidget * parent)
:   QGraphicsView{parent}
,   m_scene{new Scene{gradient, this}}
{
    setScene(m_scene);
}

void ColorGradientWidget::resizeEvent(QResizeEvent * event)
{
    QGraphicsView::resizeEvent(event);
    auto size = event->size();
    auto transform = QTransform::fromScale(size.width(), size.height());
    setTransform(transform, false);
    m_scene->resize();
}

} // namespace widgetzeug