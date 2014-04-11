
#include <QHBoxLayout>
#include <QDoubleSpinBox>

#include <reflectionzeug/Property.h>

#include <propertyguizeug/FloatingPointEditor.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
FloatingPointEditor::FloatingPointEditor(FloatingPointPropertyInterface * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_spinBox(new QDoubleSpinBox(this))
,   m_property(property)
{
    boxLayout()->addWidget(m_spinBox);
    setFocusProxy(m_spinBox);

    m_spinBox->setRange(m_property->doubleMinimum(), m_property->doubleMaximum());
	
    if (m_property->hasStep())
	m_spinBox->setSingleStep(m_property->doubleStep());
    
    m_spinBox->setDecimals(m_property->hasPrecision() ? m_property->precision() : 3);
    m_spinBox->setValue(m_property->toDouble());
    
    connect(m_spinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                  [this](double d) {
                      m_property->fromDouble(d);
                  });
}
    
FloatingPointEditor::~FloatingPointEditor()
{
}

} // namespace propertyguizeug
