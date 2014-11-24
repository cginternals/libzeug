#include <gmock/gmock.h>

#include <QColor>
#include <QList>
#include <QDebug>

#include <widgetzeug/ColorGradient.h>
#include <widgetzeug/ColorGradientProperty.h>


class ColorGradientProperty_test : public testing::Test
{
public:
};

TEST_F(ColorGradientProperty_test, StringSerialization)
{
    widgetzeug::ColorGradient gradient = widgetzeug::ColorGradient::fromList({ 
        { 221, 69, 76 }, 
        { 47, 120, 224 }, 
        { 172, 221, 122 } });
        
    widgetzeug::ColorGradient invalidGradient;
    
    auto * property1 = new reflectionzeug::Property<widgetzeug::ColorGradient>("gradient", gradient);
    auto * property2 = new reflectionzeug::Property<widgetzeug::ColorGradient>("gradient", invalidGradient);
    
    ASSERT_TRUE(property2->fromString(property1->toString()));
    ASSERT_EQ(gradient, property2->value());
}
