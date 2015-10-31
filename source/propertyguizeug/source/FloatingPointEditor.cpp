
#include <propertyguizeug/FloatingPointEditor.h>

#include <limits>

#include <QDoubleSpinBox>

#include <reflectionzeug/property/Property.h>


using namespace reflectionzeug;


namespace propertyguizeug
{


const int FloatingPointEditor::s_defaultPrecision = 3;


void FloatingPointEditor::paint(
    QPainter * painter, 
    const QStyleOptionViewItem & option, 
    reflectionzeug::AbstractFloatingPointInterface & property)
{
    reflectionzeug::AbstractProperty & prop = dynamic_cast<reflectionzeug::AbstractProperty &>(property);
    const auto prefix = QString::fromStdString(prop.option<std::string>("prefix", ""));
    const auto suffix = QString::fromStdString(prop.option<std::string>("suffix", ""));
    const auto precision = prop.option<double>("precision", s_defaultPrecision);
    const auto valueString = QString::number(property.toDouble(), 'f', precision);
    
    drawString(prefix + valueString + suffix, painter, option);
}
    
FloatingPointEditor::FloatingPointEditor(
    AbstractFloatingPointInterface * property, 
    QWidget * parent)
:   PropertyEditor{parent}
,   m_property{property}
{
    auto spinBox = new QDoubleSpinBox{this};
    
    addWidget(spinBox);
    setFocusProxy(spinBox);
    
    auto minimum = 0.0;
    auto maximum = 0.0;

    reflectionzeug::AbstractProperty * prop = dynamic_cast<reflectionzeug::AbstractProperty *>(m_property);

    assert(prop != nullptr);

    if (prop->hasOption("minimum"))
        minimum = prop->option("minimum").value<double>();
    else
        minimum = std::numeric_limits<double>::min();
        
    if (prop->hasOption("maximum"))
        maximum = prop->option("maximum").value<double>();
    else
        maximum = std::numeric_limits<double>::max();

    spinBox->setRange(minimum, maximum);
    
    if (prop->hasOption("step"))
        spinBox->setSingleStep(prop->option("step").value<double>());
        
    auto precision = 0u;
    if (prop->hasOption("precision"))
        precision = prop->option("precision").value<uint>();
    else
        precision = s_defaultPrecision;
        
    spinBox->setDecimals(precision);

    auto prefix = std::string{};
    if (prop->hasOption("prefix"))
        prefix = prop->option("prefix").value<std::string>();
    spinBox->setPrefix(QString::fromStdString(prefix));

    auto suffix = std::string{};
    if (prop->hasOption("suffix"))
        suffix = prop->option("suffix").value<std::string>();
    spinBox->setSuffix(QString::fromStdString(suffix));
    
    spinBox->setValue(m_property->toDouble());

    const auto deferred = prop->option<bool>("deferred", false);
    
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

    m_propertyChangedConnection = prop->changed.connect(
        [this, spinBox]()
        {
            spinBox->setValue(m_property->toDouble());
        });
}

FloatingPointEditor::~FloatingPointEditor()
{
}


} // namespace propertyguizeug
