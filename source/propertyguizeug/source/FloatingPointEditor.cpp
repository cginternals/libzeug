#include <propertyguizeug/FloatingPointEditor.h>

#include <limits>

#include <QDoubleSpinBox>

#include <reflectionzeug/Property.h>

using namespace reflectionzeug;
namespace propertyguizeug
{

const int FloatingPointEditor::s_defaultPrecision = 3;

void FloatingPointEditor::paint(
    QPainter * painter, 
    const QStyleOptionViewItem & option, 
    reflectionzeug::FloatingPointPropertyInterface & property)
{
    const auto prefix = QString::fromStdString(property.option<std::string>("prefix", ""));
    const auto suffix = QString::fromStdString(property.option<std::string>("suffix", ""));
    const auto precision = property.option<double>("precision", s_defaultPrecision);
    const auto valueString = QString::number(property.toDouble(), 'f', precision);
    
    drawString(prefix + valueString + suffix, painter, option);
}
    
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
        precision = s_defaultPrecision;
        
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

    const auto deferred = m_property->option<bool>("deferred", false);
    
    if (deferred)
    {
        connect(spinBox, &QAbstractSpinBox::editingFinished,
            [this, spinBox]
            {
                m_property->fromDouble(spinBox->value());
            });
    }
    else
    {
        connect(spinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this] (double d) 
            {
                m_property->fromDouble(d);
            });
    }

    m_propertyChangedConnection = m_property->valueChanged.connect(
        [this, spinBox]()
        {
            spinBox->setValue(m_property->toDouble());
        });
}

FloatingPointEditor::~FloatingPointEditor()
{
}

} // namespace propertyguizeug
