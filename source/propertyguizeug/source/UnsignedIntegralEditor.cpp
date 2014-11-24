#include <propertyguizeug/UnsignedIntegralEditor.h>

#include <reflectionzeug/UnsignedIntegralPropertyInterface.h>

#include <propertyguizeug/ULongLongSpinBox.h>

namespace propertyguizeug
{

void UnsignedIntegralEditor::paint(
    QPainter * painter, 
    const QStyleOptionViewItem & option, 
    reflectionzeug::UnsignedIntegralPropertyInterface & property)
{
    const auto prefix = QString::fromStdString(property.option<std::string>("prefix", ""));
    const auto suffix = QString::fromStdString(property.option<std::string>("suffix", ""));
    const auto valueString = QString::fromStdString(property.toString());
    
    drawString(prefix + valueString + suffix, painter, option);
}

UnsignedIntegralEditor::UnsignedIntegralEditor(
    reflectionzeug::UnsignedIntegralPropertyInterface * property, 
    QWidget * parent)
:   PropertyEditor{parent}
,   m_property{property}
{
    auto spinBox = new ULongLongSpinBox{this};
    addWidget(spinBox);
    setFocusProxy(spinBox);

    spinBox->setValue(m_property->toULongLong());

    auto minimum = 0ull;
    auto maximum = 0ull;
    
    if (m_property->hasOption("minimum"))
        minimum = m_property->option("minimum").value<qulonglong>();
    else
        minimum = std::numeric_limits<qulonglong>::min();
        
    if (m_property->hasOption("maximum"))
        maximum = m_property->option("maximum").value<qulonglong>();
    else
        maximum = std::numeric_limits<qulonglong>::max();
    
    spinBox->setRange(minimum, maximum);
	
    if (m_property->hasOption("step"))
        spinBox->setStep(m_property->option("step").value<qulonglong>());
    
    connect(spinBox, &ULongLongSpinBox::valueChanged,
        [this] (const qulonglong & value) 
        {
            m_property->fromULongLong(value);
        });
}
    
} // namespace propertyguizeug
