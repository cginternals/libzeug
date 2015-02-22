#pragma once

#include <QLabel>

#include <widgetzeug/widgetzeug_api.h>

#include <widgetzeug/ColorScheme.h>


namespace widgetzeug
{

class WIDGETZEUG_API ColorSchemeLabel : public QLabel
{
public:
    static const qreal s_defaultPadding;
    static const QSizeF s_defaultRectSize;

    static QPixmap pixmap(
        const ColorScheme * scheme,
        uint classes,
        ColorScheme::ColorVisionDeficiency deficiency,
        qreal padding = s_defaultPadding,
        const QSizeF & size = s_defaultRectSize,
        QWidget * widget = nullptr);

public:
    ColorSchemeLabel(QWidget * parent = nullptr);

    // Since this class should not be used to transfer/exchange 
    // scheme information, no getters are provided (prevent misuse).

    void setScheme(const ColorScheme * scheme);

    void setDeficiency(ColorScheme::ColorVisionDeficiency deficiency);
    void setClasses(uint classes);

    void setPadding(qreal padding);
    void setRectSize(const QSizeF & size);

protected:
    void updatePixmap();

protected:
    const ColorScheme * m_scheme;

    ColorScheme::ColorVisionDeficiency m_deficiency;
    uint m_classes;

    qreal m_padding;
    QSizeF m_rectSize;
};

} // namespace widgetzeug
