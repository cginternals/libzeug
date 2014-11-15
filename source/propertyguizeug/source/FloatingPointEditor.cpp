#include <propertyguizeug/FloatingPointEditor.h>

#include <limits>

#include <QDoubleSpinBox>

#include <reflectionzeug/Property.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
FloatingPointEditor::FloatingPointEditor(
    FloatingPointPropertyInterface * property, 
    QWidget * parent)
:   PropertyEditor{parent}
,   m_property{property}
{
    auto spinBox = new QDoubleSpinBox{this};
    
    addWidget(spinBox);
    setFocusProxy(spinBox);
    
    auto minimum = 0.0;
    auto maximum = 0.0;
    
    if (m_property->hasOption("minimum"))
        minimum = m_property->option("minimum").value<double>();
    else
        minimum = std::numeric_limits<double>::min();
        
    if (m_property->hasOption("maximum"))
        maximum = m_property->option("maximum").value<double>();
    else
        maximum = std::numeric_limits<double>::max();
    
    spinBox->setRange(minimum, maximum);
    
    if (m_property->hasOption("step"))
        spinBox->setSingleStep(m_property->option("step").value<double>());
        
    auto precision = 0u;
    if (m_property->hasOption("precision"))
        precision = m_property->option("precision").value<uint>();
    else
        precision = 3;
        
    spinBox->setDecimals(precision);

    auto prefix = std::string{};
    if (m_property->hasOption("prefix"))
        prefix = m_property->option("prefix").value<std::string>();
    spinBox->setPrefix(QString::fromStdString(prefix));

    auto suffix = std::string{};
    if (m_property->hasOption("suffix"))
        suffix = m_property->option("suffix").value<std::string>();
    spinBox->setSuffix(QString::fromStdString(suffix));
    
    spinBox->setValue(m_property->toDouble());
    
    connect(spinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [this] (double d) 
        {
            m_property->fromDouble(d);
        });
}

} // namespace propertyguizeug
