
#include <widgetzeug/ColorSchemeLabel.h>

#include <cmath>
#include <assert.h>

#include <QPainter>
#include <QPixmap>
#include <QPalette>


#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/DpiAware.h>
#include <widgetzeug/RGBABrush.hpp>


namespace widgetzeug
{

const qreal ColorSchemeLabel::s_defaultPadding{ 2.0 };

// 16 x 16 + 1px border matches well with the transparency brush that is 16 x 16 too (@see RGBABrush)
const QSizeF ColorSchemeLabel::s_defaultRectSize{ 18.0, 18.0 }; 


QPixmap ColorSchemeLabel::pixmap(
    const ColorScheme * scheme
,   const uint classes
,   const ColorVisionDeficiency deficiency
,   const bool invert
,   const qreal padding
,   const QSizeF & size
,   QWidget * parent)
{
    const auto dpiScale = DpiAware::dpiBasedScale(parent);

    QPixmap pxmap(std::ceil(((size.width() - 1) * classes + padding * (classes - 1)) * dpiScale) + 1,
        std::ceil(size.height() * dpiScale));

    pxmap.fill(Qt::transparent);

    auto pen = QPen(QPalette().dark().color());
    pen.setWidthF(1.0 / DpiAware::devicePixelRatio(parent));

    auto R = QRectF(0.f, 0.f, (size.width() - 1) * dpiScale, (size.height() - 1) * dpiScale);

    const auto colors = scheme ? scheme->colors(classes) : QVector<QColor>();    
    {
        QPainter painter(&pxmap);
        painter.setPen(pen);
        for (uint i = 0; i < classes; ++i)
        {
            if (colors.isEmpty())
                painter.setBrush(Qt::NoBrush);
            else
                painter.setBrush(RGBABrush(daltonize(colors[invert ? classes - i - 1 : i], deficiency)));

            R.moveLeft((R.width() + padding * dpiScale) * i);
            painter.setBrushOrigin(R.left() + pen.widthF(), R.bottom());
            painter.drawRect(R);
        }
    }
    return pxmap;
}

ColorSchemeLabel::ColorSchemeLabel(QWidget * parent)
:   QLabel(parent)
, m_scheme{ nullptr }
, m_deficiency{ ColorVisionDeficiency::None }
, m_classes { 1 }
, m_inverted{ false }
, m_padding{ s_defaultPadding }
, m_rectSize{ s_defaultRectSize }
{
}

void ColorSchemeLabel::setScheme(const ColorScheme * scheme)
{
    if (scheme == m_scheme)
        return;

    m_scheme = scheme;
    updatePixmap();
}

void ColorSchemeLabel::setClasses(const uint classes)
{
    if (classes == m_classes)
        return;

    m_classes = classes;
    updatePixmap();
}

void ColorSchemeLabel::setDeficiency(const ColorVisionDeficiency deficiency)
{
    if (deficiency == m_deficiency)
        return;

    m_deficiency = deficiency;
    updatePixmap();
}

void ColorSchemeLabel::setInverted(const bool inverted)
{
    if (inverted == m_inverted)
        return;

    m_inverted = inverted;
    updatePixmap();
}

void ColorSchemeLabel::setPadding(const qreal padding)
{
    if (padding == m_padding)
        return;

    m_padding = padding;
    updatePixmap();
}

void ColorSchemeLabel::setRectSize(const QSizeF & size)
{
    if (size == m_rectSize)
        return;

    m_rectSize = size;
    updatePixmap();
}

void ColorSchemeLabel::updatePixmap()
{
    setPixmap(pixmap(m_scheme, m_classes, m_deficiency, m_inverted, m_padding, m_rectSize, this));
    setMinimumSize(QLabel::pixmap()->size());    
}

} // namespace widgetzeug
