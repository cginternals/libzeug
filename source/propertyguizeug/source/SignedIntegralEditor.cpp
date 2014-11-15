#include <propertyguizeug/SignedIntegralEditor.h>

#include <reflectionzeug/SignedIntegralPropertyInterface.h>

#include <propertyguizeug/LongLongSpinBox.h>

namespace propertyguizeug
{

SignedIntegralEditor::SignedIntegralEditor(
    reflectionzeug::SignedIntegralPropertyInterface * property, 
    QWidget * parent)
:   PropertyEditor{parent}
,   m_property{property}
{
    auto spinBox = new LongLongSpinBox{this};
    
    addWidget(spinBox);
    setFocusProxy(spinBox);

    spinBox->setValue(m_property->toLongLong());

    auto minimum = 0ll;
    auto maximum = 0ll;
    
    if (m_property->hasOption("minimum"))
        minimum = m_property->option("minimum").value<qlonglong>();
    else
        minimum = std::numeric_limits<qlonglong>::min();
        
    if (m_property->hasOption("maximum"))
        maximum = m_property->option("maximum").value<qlonglong>();
    else
        maximum = std::numeric_limits<qlonglong>::max();
    
    spinBox->setRange(minimum, maximum);
    
    if (m_property->hasOption("step"))
        spinBox->setStep(m_property->option("step").value<qlonglong>());
    
    connect(spinBox, &LongLongSpinBox::valueChanged,
        [this] (const qlonglong & value) 
        {
            m_property->fromLongLong(value);
        });
}
    
} // namespace propertyguizeug
