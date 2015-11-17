#include <propertyguizeug/UnsignedIntegralEditor.h>

#include <reflectionzeug/property/AbstractProperty.h>
#include <reflectionzeug/property/AbstractUnsignedIntegralInterface.h>

#include <stringzeug/conversion.h>

#include <propertyguizeug/ULongLongSpinBox.h>

using namespace reflectionzeug;
namespace propertyguizeug
{

void UnsignedIntegralEditor::paint(
    QPainter * painter, 
    const QStyleOptionViewItem & option, 
    AbstractUnsignedIntegralInterface & property)
{
    AbstractProperty & prop = dynamic_cast<AbstractProperty &>(property);
    const auto prefix = QString::fromStdString(prop.option<std::string>("prefix", ""));
    const auto suffix = QString::fromStdString(prop.option<std::string>("suffix", ""));
    const auto valueString = QString::fromStdString(stringzeug::toString(property.toULongLong()));

    drawString(prefix + valueString + suffix, painter, option);
}

UnsignedIntegralEditor::UnsignedIntegralEditor(
    AbstractUnsignedIntegralInterface * property, 
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

    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);

    if (prop == nullptr)
    {
        return;
    }

    if (prop->hasOption("minimum"))
        minimum = prop->option("minimum").value<qulonglong>();
    else
        minimum = std::numeric_limits<qulonglong>::min();
        
    if (prop->hasOption("maximum"))
        maximum = prop->option("maximum").value<qulonglong>();
    else
        maximum = std::numeric_limits<qulonglong>::max();
    
    spinBox->setRange(minimum, maximum);
	
    if (prop->hasOption("step"))
        spinBox->setStep(prop->option("step").value<qulonglong>());
    
    const auto deferred = prop->option<bool>("deferred", false);

    if (deferred)
    {
        connect(spinBox, &QAbstractSpinBox::editingFinished,
            [this, spinBox]
        {
            m_property->fromULongLong(spinBox->value());
        });
    }
    else
    {
        connect(spinBox, &ULongLongSpinBox::valueChanged,
            [this](const qulonglong & value)
            {
                m_property->fromULongLong(value);
            });
    }

    m_propertyChangedConnection = prop->changed.connect(
        [this, spinBox]()
        {
            spinBox->setValue(m_property->toULongLong());
        });
}

UnsignedIntegralEditor::~UnsignedIntegralEditor()
{
}

} // namespace propertyguizeug
