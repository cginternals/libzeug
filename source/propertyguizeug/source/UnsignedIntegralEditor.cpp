
#include <QHBoxLayout>

#include <reflectionzeug/UnsignedIntegralPropertyInterface.h>

#include <propertyguizeug/UnsignedIntegralEditor.h>
#include <propertyguizeug/ULongLongSpinBox.h>


namespace propertyguizeug
{

UnsignedIntegralEditor::UnsignedIntegralEditor(
    reflectionzeug::UnsignedIntegralPropertyInterface * property, 
    QWidget * parent)
:   PropertyEditor(parent)
,   m_spinBox(new ULongLongSpinBox(this))
,   m_property(property)
{
    boxLayout()->addWidget(m_spinBox);
    setFocusProxy(m_spinBox);

    m_spinBox->setValue(m_property->toULongLong());

    qulonglong minimum, maximum;
    
    if (m_property->hasOption("minimum"))
        minimum = m_property->option("minimum").value<qulonglong>();
    else
        minimum = std::numeric_limits<qulonglong>::min();
        
    if (m_property->hasOption("maximum"))
        maximum = m_property->option("maximum").value<qulonglong>();
    else
        maximum = std::numeric_limits<qulonglong>::max();
    
    m_spinBox->setRange(minimum, maximum);
    
    if (m_property->hasOption("step"))
        m_spinBox->setStep(m_property->option("step").value<qulonglong>());

    std::string prefix;
    if (m_property->hasOption("prefix"))
        prefix = m_property->option("prefix").value<std::string>();
    m_spinBox->setPrefix(QString::fromStdString(prefix));

    std::string suffix;
    if (m_property->hasOption("suffix"))
        suffix = m_property->option("suffix").value<std::string>();
    m_spinBox->setSuffix(QString::fromStdString(suffix));

    
    connect(m_spinBox, &ULongLongSpinBox::valueChanged,
        [this] (const qulonglong & value) 
        {
            m_property->fromULongLong(value);
        });
}
    
UnsignedIntegralEditor::~UnsignedIntegralEditor()
{
}
    
} // namespace propertyguizeug
