#include <gmock/gmock.h>

#include <QColor>
#include <QImage>
#include <QList>

#include <widgetzeug/ColorGradient.h>
#include <widgetzeug/ColorScheme.h>


class ColorGradient_test : public testing::Test
{
public:
    ColorGradient_test()
    :   m_colors({ { 160, 89, 0 }, { 5, 189, 136 }, { 67, 2, 127 } })
    ,   m_positions({ 0.0, 0.5, 1.0 })
    {
    }
    
protected:
    QList<QColor> m_colors;
    QList<qreal> m_positions;
};

TEST_F(ColorGradient_test, ConversionFromColorScheme)
{
    widgetzeug::ColorScheme scheme;
    scheme.setColors(m_colors);
    
    widgetzeug::ColorGradient gradient = widgetzeug::ColorGradient::fromScheme(&scheme, 3);
    widgetzeug::ColorGradientStops stops = gradient.stops();
    
    ASSERT_EQ(3, stops.size());
    
    for (int i = 0; i < stops.count(); ++i)
    {
        ASSERT_EQ(m_positions[i], stops.at(i).position());
        ASSERT_EQ(m_colors[i], stops.at(i).color());
    } 
}

TEST_F(ColorGradient_test, ConversionFromColorList)
{        
    widgetzeug::ColorGradient gradient = widgetzeug::ColorGradient::fromList(m_colors);
    widgetzeug::ColorGradientStops stops = gradient.stops();
    
    ASSERT_EQ(stops.count(), 3);
        
    for (int i = 0; i < stops.count(); ++i)
    {
        ASSERT_EQ(m_positions[i], stops.at(i).position());
        ASSERT_EQ(m_colors[i], stops.at(i).color());
    }    
}

TEST_F(ColorGradient_test, CreateImage)
{        
    widgetzeug::ColorGradient gradient = widgetzeug::ColorGradient::fromList(m_colors);
    
    QImage image = gradient.image(256);
    ASSERT_EQ(QSize(256, 1), image.size());
}

TEST_F(ColorGradient_test, EqualityAndInequality)
{
    widgetzeug::ColorGradient gradient1 = widgetzeug::ColorGradient::fromList(m_colors);
    widgetzeug::ColorGradient gradient2 = widgetzeug::ColorGradient::fromList(m_colors);
    
    ASSERT_EQ(gradient1, gradient2);
    
    gradient2.setType(widgetzeug::ColorGradientType::Discrete);
    ASSERT_NE(gradient1, gradient2);
}
