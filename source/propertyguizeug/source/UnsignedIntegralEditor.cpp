
#include <QHBoxLayout>

#include <reflectionzeug/UnsignedIntegralPropertyInterface.h>

#include <propertyguizeug/UnsignedIntegralEditor.h>
#include <propertyguizeug/UnsignedLongLongSpinBox.h>


namespace propertyguizeug
{

UnsignedIntegralEditor::UnsignedIntegralEditor(
    reflectionzeug::UnsignedIntegralPropertyInterface * property, 
    QWidget * parent)
:   PropertyEditor(parent)
,   m_spinBox(new UnsignedLongLongSpinBox(this))
,   m_property(property)
{
    boxLayout()->addWidget(m_spinBox);
    setFocusProxy(m_spinBox);

    m_spinBox->setValue(m_property->toULongLong());
    m_spinBox->setRange(m_property->uLongLongMinimum(),
                        m_property->uLongLongMaximum());

    if (m_property->hasStep())
        m_spinBox->setStep(m_property->uLongLongStep());
    
    connect(m_spinBox, &UnsignedLongLongSpinBox::valueChanged,
        [this] (const unsigned long long & value) 
        {
            m_property->fromULongLong(value);
        });
}
    
UnsignedIntegralEditor::~UnsignedIntegralEditor()
{
}
    
} // namespace propertyguizeug
