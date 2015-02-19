#pragma once

#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/DpiAwareGraphicsView.h>


namespace widgetzeug
{

class ColorSchemeGraphicsItem;


class SingleColorSchemeGraphicsView : public DpiAwareGraphicsView
{
public:
    SingleColorSchemeGraphicsView(QWidget * parent = nullptr);

    void setScheme(ColorScheme * scheme);
    ColorScheme * scheme();

    void setDeficiency(ColorScheme::ColorVisionDeficiency deficiency);
    ColorScheme::ColorVisionDeficiency deficiency() const;

    void setClasses(int classes);
    int classes() const;

private:
    ColorSchemeGraphicsItem * m_item;
};

} // namespace widgetzeug
