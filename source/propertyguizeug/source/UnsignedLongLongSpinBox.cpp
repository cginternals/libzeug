
#include <limits>
#include <algorithm>

#include <QLineEdit>

#include <reflectionzeug/util.h>

#include <propertyguizeug/UnsignedLongLongSpinBox.h>


namespace propertyguizeug
{

UnsignedLongLongSpinBox::UnsignedLongLongSpinBox(QWidget * parent)
:   QAbstractSpinBox(parent) 
,   m_min(std::numeric_limits<unsigned long long>::lowest())
,   m_max(std::numeric_limits<unsigned long long>::max())
,   m_step(1)
,   m_value(m_min)
{
    connect(this, &QAbstractSpinBox::editingFinished,
            this, &UnsignedLongLongSpinBox::onEditingFinished);
}

void UnsignedLongLongSpinBox::fixup(QString & input) const
{
    QAbstractSpinBox::fixup(input);
}

void UnsignedLongLongSpinBox::stepBy(int steps)
{
    setValue(m_value + steps * m_step);
}

QValidator::State UnsignedLongLongSpinBox::validate(QString & input, int & pos) const
{
    return QAbstractSpinBox::validate(input, pos);
}
    
unsigned long long UnsignedLongLongSpinBox::value() const
{
    return m_value;
}

void UnsignedLongLongSpinBox::setValue(const unsigned long long & value)
{
    unsigned long long clampedValue = std::min(m_max, std::max(value, m_min));
    m_value = clampedValue;
    lineEdit()->setText(QString::fromStdString(reflectionzeug::util::toString(m_value)));
    emit valueChanged(m_value);
}

unsigned long long UnsignedLongLongSpinBox::minimum() const
{
    return m_min;
}

void UnsignedLongLongSpinBox::setMinimum(const unsigned long long & minimum)
{
    m_min = minimum;

    if (m_max < m_min)
        m_max = m_min;
}

unsigned long long UnsignedLongLongSpinBox::maximum() const
{
    return m_max;
}

void UnsignedLongLongSpinBox::setMaximum(const unsigned long long & maximum)
{
    m_max = maximum;

    if (m_min > m_max)
        m_min = m_max;
}

unsigned long long UnsignedLongLongSpinBox::step() const
{
    return m_step;
}

void UnsignedLongLongSpinBox::setStep(const unsigned long long & step)
{
    m_step = step;
}

void UnsignedLongLongSpinBox::setRange(
    const unsigned long long & min,
    const unsigned long long & max)
{
    setMinimum(min);
    setMaximum(max);    
}

void UnsignedLongLongSpinBox::onEditingFinished()
{
    if (!reflectionzeug::util::matchesRegex(text().toStdString(), "\\+?\\d+"))
        return;
    
    unsigned long long value = reflectionzeug::util::fromString<unsigned long long>(text().toStdString()); 
    
    setValue(value);
}
    
QAbstractSpinBox::StepEnabled UnsignedLongLongSpinBox::stepEnabled() const
{
    StepEnabled enabled;
    
    if (m_value > m_min)
        enabled |= QAbstractSpinBox::StepDownEnabled;
    
    if (m_value < m_max)
        enabled |= QAbstractSpinBox::StepUpEnabled;
    
    return enabled;
}
    
} // namespace propertyguizeug
