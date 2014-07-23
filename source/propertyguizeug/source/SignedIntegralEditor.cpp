
#include <QHBoxLayout>

#include <reflectionzeug/SignedIntegralPropertyInterface.h>

#include <propertyguizeug/SignedIntegralEditor.h>
#include <propertyguizeug/LongLongSpinBox.h>


namespace propertyguizeug
{

SignedIntegralEditor::SignedIntegralEditor(
    reflectionzeug::SignedIntegralPropertyInterface * property, 
    QWidget * parent)
:   PropertyEditor(parent)
,   m_spinBox(new LongLongSpinBox(this))
,   m_property(property)
{
    boxLayout()->addWidget(m_spinBox);
    setFocusProxy(m_spinBox);

    double minimum, maximum;
    
    if (m_property->hasOption("minimum"))
        minimum = m_property->option("minimum").value<qlonglong>();
    else
        minimum = std::numeric_limits<qlonglong>::min();
        
    if (m_property->hasOption("maximum"))
        maximum = m_property->option("maximum").value<qlonglong>();
    else
        maximum = std::numeric_limits<qlonglong>::max();
    
    m_spinBox->setRange(minimum, maximum);
    
    if (m_property->hasOption("step"))
        m_spinBox->setStep(m_property->option("step").value<qlonglong>());
    
    connect(m_spinBox, &LongLongSpinBox::valueChanged,
        [this] (const qlonglong & value) 
        {
            m_property->fromULongLong(value);
        });
}
    
} // namespace propertyguizeug
