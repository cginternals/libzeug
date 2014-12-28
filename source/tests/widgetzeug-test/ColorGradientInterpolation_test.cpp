#include <gmock/gmock.h>

#include <QColor>
#include <QDebug>
#include <QList>

#include <widgetzeug/ColorGradient.h>


class ColorGradientInterpolation_test : public testing::Test
{
public:
    ColorGradientInterpolation_test()
    :   m_colors({ { 221, 69, 76 }, { 47, 120, 224 }, { 172, 221, 122 } })
    ,   m_positions({ 0.0, 0.5, 1.0 })
    {
        widgetzeug::ColorGradientStops stops;
        for (int i = 0; i < 3; ++i)
            stops << widgetzeug::ColorGradientStop(m_colors[i], m_positions[i]);
        
        m_gradient = widgetzeug::ColorGradient(stops);
    }
    
protected:
    const QList<QColor> m_colors;
    const QList<qreal> m_positions;
    widgetzeug::ColorGradient m_gradient;
};

TEST_F(ColorGradientInterpolation_test, LinearPureColors)
{
    m_gradient.setType(widgetzeug::ColorGradientType::Linear);
    ASSERT_EQ(m_colors[0], m_gradient.interpolateColor(0.0));
    ASSERT_EQ(m_colors[1], m_gradient.interpolateColor(0.5));
    ASSERT_EQ(m_colors[2], m_gradient.interpolateColor(1.0));
}

TEST_F(ColorGradientInterpolation_test, DiscretePureColors)
{
    m_gradient.setType(widgetzeug::ColorGradientType::Discrete);
    m_gradient.setSteps(3u);
    ASSERT_EQ(m_colors[0], m_gradient.interpolateColor(0.0));
    ASSERT_EQ(m_colors[1], m_gradient.interpolateColor(0.5));
    ASSERT_EQ(m_colors[2], m_gradient.interpolateColor(1.0));
}

TEST_F(ColorGradientInterpolation_test, MatzePureColors)
{
    m_gradient.setType(widgetzeug::ColorGradientType::Matze);
    m_gradient.setSteps(3u);
    ASSERT_EQ(m_colors[0], m_gradient.interpolateColor(0.0));
    ASSERT_EQ(m_colors[1], m_gradient.interpolateColor(1.0 / 3));
    ASSERT_EQ(m_colors[2], m_gradient.interpolateColor(2.0 / 3));
}

/** TODO: This passes right now, but it very fragile.
 */
TEST_F(ColorGradientInterpolation_test, LinearColors)
{
    m_gradient.setType(widgetzeug::ColorGradientType::Linear);

    ASSERT_EQ(QColor::fromRgbF(109.5 / 255, 170.5 / 255, 173.0 / 255).rgba(), m_gradient.interpolateColor(0.75).rgba());
}
