#include <propertyguizeug/SignedIntegralEditor.h>

#include <reflectionzeug/property/AbstractProperty.h>
#include <reflectionzeug/property/AbstractSignedIntegralInterface.h>

#include <stringzeug/conversion.h>

#include <propertyguizeug/LongLongSpinBox.h>

using namespace reflectionzeug;
namespace propertyguizeug
{

void SignedIntegralEditor::paint(
    QPainter * painter, 
    const QStyleOptionViewItem & option, 
    AbstractSignedIntegralInterface & property)
{
    AbstractProperty & prop = dynamic_cast<AbstractProperty &>(property);
    const auto prefix = QString::fromStdString(prop.option<std::string>("prefix", ""));
    const auto suffix = QString::fromStdString(prop.option<std::string>("suffix", ""));
    const auto valueString = QString::fromStdString(stringzeug::toString(property.toLongLong()));

    drawString(prefix + valueString + suffix, painter, option);
}

SignedIntegralEditor::SignedIntegralEditor(
    AbstractSignedIntegralInterface * property, 
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

    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);
    if (prop->hasOption("minimum"))
        minimum = prop->option("minimum").value<qlonglong>();
    else
        minimum = std::numeric_limits<qlonglong>::min();
        
    if (prop->hasOption("maximum"))
        maximum = prop->option("maximum").value<qlonglong>();
    else
        maximum = std::numeric_limits<qlonglong>::max();
    
    spinBox->setRange(minimum, maximum);
    
    if (prop->hasOption("step"))
        spinBox->setStep(prop->option("step").value<qlonglong>());

    const auto deferred = prop->option<bool>("deferred", false);

    if (deferred)
    {
        connect(spinBox, &QAbstractSpinBox::editingFinished,
            [this, spinBox]
        {
            m_property->fromLongLong(spinBox->value());
        });
    }
    else
    {
        connect(spinBox, &LongLongSpinBox::valueChanged,
            [this](const qlonglong & value)
            {
                m_property->fromLongLong(value);
            });
    }

    m_propertyChangedConnection = prop->changed.connect(
        [this, spinBox]()
        {
            spinBox->setValue(m_property->toLongLong());
        });
}

SignedIntegralEditor::~SignedIntegralEditor()
{
    m_propertyChangedConnection.disconnect();
}
    
} // namespace propertyguizeug
