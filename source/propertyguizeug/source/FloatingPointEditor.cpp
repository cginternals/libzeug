
#include <limits>

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
    
    double minimum, maximum;
    
    if (m_property->hasOption("minimum"))
        minimum = m_property->option("minimum").value<double>();
    else
        minimum = -std::numeric_limits<double>::max();
        
    if (m_property->hasOption("maximum"))
        maximum = m_property->option("maximum").value<double>();
    else
        maximum = std::numeric_limits<double>::max();
    
    m_spinBox->setRange(minimum, maximum);
    
    if (m_property->hasOption("step"))
        m_spinBox->setSingleStep(m_property->option("step").value<double>());
        
    uint precision;
    if (m_property->hasOption("precision"))
        precision = m_property->option("precision").value<uint>();
    else
        precision = 3;
        
    m_spinBox->setDecimals(precision);

    std::string prefix;
    if (m_property->hasOption("prefix"))
        prefix = m_property->option("prefix").value<std::string>();
    m_spinBox->setPrefix(QString::fromStdString(prefix));

    std::string suffix;
    if (m_property->hasOption("suffix"))
        suffix = m_property->option("suffix").value<std::string>();
    m_spinBox->setSuffix(QString::fromStdString(suffix));
    
    m_spinBox->setValue(m_property->toDouble());
    
    connect(m_spinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                  [this](double d) {
                      m_property->fromDouble(d);
                  });
}

} // namespace propertyguizeug
