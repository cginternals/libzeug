
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

    m_spinBox->setValue(m_property->toULongLong());
    m_spinBox->setRange(m_property->uLongLongMinimum(),
                        m_property->uLongLongMaximum());

    if (m_property->hasStep())
        m_spinBox->setStep(m_property->uLongLongStep());
    
    connect(m_spinBox, &LongLongSpinBox::valueChanged,
        [this] (const unsigned long long & value) 
        {
            m_property->fromULongLong(value);
        });
}
    
SignedIntegralEditor::~SignedIntegralEditor()
{
}
    
} // namespace propertyguizeug
