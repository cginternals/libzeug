#pragma once

#include <QLabel>

#include <widgetzeug/widgetzeug_api.h>

#include <widgetzeug/ColorVisionDeficiency.h>


namespace widgetzeug
{

class ColorScheme;

class WIDGETZEUG_API ColorSchemeLabel : public QLabel
{
public:
    static const qreal s_defaultPadding;
    static const QSizeF s_defaultRectSize;

    static QPixmap pixmap(
        const ColorScheme * scheme,
        uint classes,
        ColorVisionDeficiency deficiency,
        bool invert = false,
        qreal padding = s_defaultPadding,
        const QSizeF & size = s_defaultRectSize,
        QWidget * widget = nullptr);

public:
    ColorSchemeLabel(QWidget * parent = nullptr);
    virtual ~ColorSchemeLabel() = default;

    // Since this class should not be used to transfer/exchange 
    // scheme information, no getters are provided (prevent misuse).

    void setScheme(const ColorScheme * scheme);

    void setDeficiency(ColorVisionDeficiency deficiency);
    void setClasses(uint classes);
    void setInverted(bool invert);

    void setPadding(qreal padding);
    void setRectSize(const QSizeF & size);

protected:
    void updatePixmap();

protected:
    const ColorScheme * m_scheme;

    ColorVisionDeficiency m_deficiency;
    uint m_classes;
    bool m_inverted;

    qreal m_padding;
    QSizeF m_rectSize;
};

} // namespace widgetzeug
