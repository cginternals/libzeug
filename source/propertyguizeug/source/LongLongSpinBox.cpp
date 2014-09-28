
#include <limits>
#include <algorithm>

#include <QLineEdit>
#include <QLocale>

#include <propertyguizeug/LongLongSpinBox.h>


namespace propertyguizeug
{

LongLongSpinBox::LongLongSpinBox(QWidget * parent)
:   QAbstractSpinBox(parent) 
,   m_min(std::numeric_limits<qlonglong>::lowest())
,   m_max(std::numeric_limits<qlonglong>::max())
,   m_step(1)
,   m_value(m_min)
{
    connect(this, &QAbstractSpinBox::editingFinished,
            this, &LongLongSpinBox::onEditingFinished);
}

void LongLongSpinBox::fixup(QString & input) const
{
    input.remove(locale().groupSeparator());
}

void LongLongSpinBox::stepBy(int steps)
{
    setValue(m_value + steps * m_step);
}

QValidator::State LongLongSpinBox::validate(QString & input, int & pos) const
{
    QValidator::State state;
    validateAndInterpret(input, pos, state);
    return state;
}
    
qlonglong LongLongSpinBox::value() const
{
    return m_value;
}

void LongLongSpinBox::setValue(qlonglong value)
{
    qlonglong clampedValue = std::min(m_max, std::max(value, m_min));

    if (clampedValue == m_value)
        return;
    
    m_value = clampedValue;
    lineEdit()->setText(textFromValue(m_value));
    emit valueChanged(m_value);
}

qlonglong LongLongSpinBox::minimum() const
{
    return m_min;
}

void LongLongSpinBox::setMinimum(qlonglong minimum)
{
    m_min = minimum;

    if (m_max < m_min)
        m_max = m_min;
}

qlonglong LongLongSpinBox::maximum() const
{
    return m_max;
}

void LongLongSpinBox::setMaximum(qlonglong maximum)
{
    m_max = maximum;

    if (m_min > m_max)
        m_min = m_max;
}

qlonglong LongLongSpinBox::step() const
{
    return m_step;
}

void LongLongSpinBox::setStep(qlonglong step)
{
    m_step = step;
}

void LongLongSpinBox::setRange(
    qlonglong min,
    qlonglong max)
{
    setMinimum(min);
    setMaximum(max);    
}

void LongLongSpinBox::onEditingFinished()
{
    qlonglong value = valueFromText(text());
    
    qlonglong clampedValue = std::min(m_max, std::max(value, m_min));

    if (clampedValue == m_value)
        return;
    
    m_value = clampedValue;
    emit valueChanged(m_value);
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

QString LongLongSpinBox::textFromValue(qlonglong value)
{
    QString str;

    str = locale().toString(value);

    if (value >= 1000 || value <= -1000)
        str.remove(locale().groupSeparator());

    return str;
}

qlonglong LongLongSpinBox::valueFromText(const QString & text)
{
    int pos = lineEdit()->cursorPosition();
    QValidator::State state = QValidator::Acceptable;
    return validateAndInterpret(text, pos, state);
}

qlonglong LongLongSpinBox::validateAndInterpret(
    const QString & input, 
    int & pos, 
    QValidator::State & state) const
{
    qlonglong num = m_min;

    if (input.isEmpty() 
        || (m_min < 0 && input == QLatin1String("-"))
        || (m_max >= 0 && input == QLatin1String("+")))
    {
        state = QValidator::Intermediate;
    }
    else if (input.startsWith("-") && m_min >= 0)
    {
        state = QValidator::Invalid;
    }
    else
    {
        bool ok = false;
        num = locale().toLongLong(input, &ok);

        if (!ok 
            && input.contains(locale().groupSeparator()) 
            && (m_max >= 1000 || m_min <= -1000))
        {
            QString copy = input;
            copy.remove(locale().groupSeparator());
            num = locale().toLongLong(copy, &ok);
        }

        if (!ok)
            state = QValidator::Invalid;
        else if (num >= m_min && num <= m_max)
            state = QValidator::Acceptable;
        else if (m_min == m_max)
            state = QValidator::Invalid;
        else
        {
            if ((num >= 0 || num > m_max) || (num < 0 && num < m_min))
                state = QValidator::Invalid;
            else
                state = QValidator::Intermediate;
        }
    }

    if (state != QValidator::Acceptable)
        num = m_max > 0 ? m_min : m_max;

    return num;
}
    
} // namespace propertyguizeug
