
#include <limits>
#include <algorithm>

#include <QLineEdit>

#include <reflectionzeug/util.h>

#include <propertyguizeug/LongLongSpinBox.h>


namespace propertyguizeug
{

LongLongSpinBox::LongLongSpinBox(QWidget * parent)
:   QAbstractSpinBox(parent) 
,   m_min(std::numeric_limits<long long>::lowest())
,   m_max(std::numeric_limits<long long>::max())
,   m_step(1)
,   m_value(m_min)
{
    connect(this, &QAbstractSpinBox::editingFinished,
            this, &LongLongSpinBox::onEditingFinished);
}

void LongLongSpinBox::fixup(QString & input) const
{
    QAbstractSpinBox::fixup(input);
}

void LongLongSpinBox::stepBy(int steps)
{
    setValue(m_value + steps * m_step);
}

QValidator::State LongLongSpinBox::validate(QString & input, int & pos) const
{
    return QAbstractSpinBox::validate(input, pos);
}
    
long long LongLongSpinBox::value() const
{
    return m_value;
}

void LongLongSpinBox::setValue(const long long & value)
{
    long long clampedValue = std::min(m_max, std::max(value, m_min));
    m_value = clampedValue;
    lineEdit()->setText(QString::fromStdString(reflectionzeug::util::toString(m_value)));
    emit valueChanged(m_value);
}

long long LongLongSpinBox::minimum() const
{
    return m_min;
}

void LongLongSpinBox::setMinimum(const long long & minimum)
{
    m_min = minimum;

    if (m_max < m_min)
        m_max = m_min;
}

long long LongLongSpinBox::maximum() const
{
    return m_max;
}

void LongLongSpinBox::setMaximum(const long long & maximum)
{
    m_max = maximum;

    if (m_min > m_max)
        m_min = m_max;
}

long long LongLongSpinBox::step() const
{
    return m_step;
}

void LongLongSpinBox::setStep(const long long & step)
{
    m_step = step;
}

void LongLongSpinBox::setRange(
    const long long & min,
    const long long & max)
{
    setMinimum(min);
    setMaximum(max);    
}

void LongLongSpinBox::onEditingFinished()
{
    if (!reflectionzeug::util::matchesRegex(text().toStdString(), "(-|\\+)?\\d+"))
        return;
    
    long long value = reflectionzeug::util::fromString<long long>(text().toStdString()); 
    
    setValue(value);
}
    
QAbstractSpinBox::StepEnabled LongLongSpinBox::stepEnabled() const
{
    StepEnabled enabled;
    
    if (m_value > m_min)
        enabled |= QAbstractSpinBox::StepDownEnabled;
    
    if (m_value < m_max)
        enabled |= QAbstractSpinBox::StepUpEnabled;
    
    return enabled;
}
    
} // namespace propertyguizeug
