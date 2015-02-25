#include <gmock/gmock.h>

#include <QColor>
#include <QList>
#include <QDebug>

#include <widgetzeug/ColorGradient.h>
#include <widgetzeug/ColorGradientProperty.h>


using namespace reflectionzeug;
using namespace widgetzeug;

class ColorGradientProperty_test : public testing::Test
{
public:
};

TEST_F(ColorGradientProperty_test, StringSerialization)
{
    auto gradient = ColorGradient::fromList({
        { 221, 69, 76 }, 
        { 47, 120, 224 }, 
        { 172, 221, 122 } });
        
    auto invalidGradient = ColorGradient{};
    
    auto property1 = new Property<ColorGradient>("gradient",
        [&gradient]() { return gradient; },
        [&gradient](const ColorGradient & value) { gradient = value; });
    
    auto property2 = new Property<ColorGradient>("gradient",
        [&invalidGradient]() { return invalidGradient; },
        [&invalidGradient](const ColorGradient & value) { invalidGradient = value; });
    
    ASSERT_TRUE(property2->fromString(property1->toString()));
    ASSERT_EQ(gradient, property2->value());
}
