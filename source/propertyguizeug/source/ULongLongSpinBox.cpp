
#include <limits>
#include <algorithm>

#include <QLineEdit>
#include <QDebug>
#include <QLocale>

#include <reflectionzeug/util.h>

#include <propertyguizeug/ULongLongSpinBox.h>


namespace propertyguizeug
{

ULongLongSpinBox::ULongLongSpinBox(QWidget * parent)
:   QAbstractSpinBox(parent) 
,   m_min(std::numeric_limits<qulonglong>::lowest())
,   m_max(std::numeric_limits<qulonglong>::max())
,   m_step(1)
,   m_value(m_min)
{
    setInputMethodHints(Qt::ImhDigitsOnly);

    connect(this, &QAbstractSpinBox::editingFinished,
            this, &ULongLongSpinBox::onEditingFinished);
}

void ULongLongSpinBox::fixup(QString & input) const
{
    input.remove(locale().groupSeparator());
}

void ULongLongSpinBox::stepBy(int steps)
{
    setValue(m_value + steps * m_step);
}

QValidator::State ULongLongSpinBox::validate(QString & input, int & pos) const
{
    QValidator::State state;
    validateAndInterpret(input, pos, state);
    return state;
}
    
qulonglong ULongLongSpinBox::value() const
{
    return m_value;
}

void ULongLongSpinBox::setValue(qulonglong value)
{
    qulonglong clampedValue = std::min(m_max, std::max(value, m_min));

    if (clampedValue == m_value)
        return;
    
    m_value = clampedValue;
    lineEdit()->setText(textFromValue(m_value));
    emit valueChanged(m_value);
}

qulonglong ULongLongSpinBox::minimum() const
{
    return m_min;
}

void ULongLongSpinBox::setMinimum(qulonglong minimum)
{
    m_min = minimum;

    if (m_max < m_min)
        m_max = m_min;
}

qulonglong ULongLongSpinBox::maximum() const
{
    return m_max;
}

void ULongLongSpinBox::setMaximum(qulonglong maximum)
{
    m_max = maximum;

    if (m_min > m_max)
        m_min = m_max;
}

qulonglong ULongLongSpinBox::step() const
{
    return m_step;
}

void ULongLongSpinBox::setStep(qulonglong step)
{
    m_step = step;
}

void ULongLongSpinBox::setRange(
    qulonglong min,
    qulonglong max)
{
    setMinimum(min);
    setMaximum(max);    
}

void ULongLongSpinBox::onEditingFinished()
{   
    qulonglong value = valueFromText(text());
    
    qulonglong clampedValue = std::min(m_max, std::max(value, m_min));

    if (clampedValue == m_value)
        return;
    
    m_value = clampedValue;
    emit valueChanged(m_value);
}
    
QAbstractSpinBox::StepEnabled ULongLongSpinBox::stepEnabled() const
{
    StepEnabled enabled;
    
    if (m_value > m_min)
        enabled |= QAbstractSpinBox::StepDownEnabled;
    
    if (m_value < m_max)
        enabled |= QAbstractSpinBox::StepUpEnabled;
    
    return enabled;
}
    
QString ULongLongSpinBox::textFromValue(qulonglong value)
{
    QString str;

    str = locale().toString(value);

    if (value >= 1000)
        str.remove(locale().groupSeparator());

    return str;
}

qulonglong ULongLongSpinBox::valueFromText(const QString & text)
{
    int pos = lineEdit()->cursorPosition();
    QValidator::State state = QValidator::Acceptable;
    return validateAndInterpret(text, pos, state);
}
    
qulonglong ULongLongSpinBox::validateAndInterpret(
    const QString & input, 
    int & pos, 
    QValidator::State & state) const
{
    qulonglong num = m_min;

    if (input.isEmpty() || input == QLatin1String("+"))
    {
        state = QValidator::Intermediate;
    }
    else if (input.startsWith(QLatin1String("-")))
    {
        state = QValidator::Invalid;
    }
    else
    {
        bool ok = false;
        num = locale().toULongLong(input, &ok);
        if (!ok && input.contains(locale().groupSeparator()) && m_max >= 1000)
        {
            QString copy = input;
            copy.remove(locale().groupSeparator());
            num = locale().toULongLong(copy, &ok);
        }

        if (!ok)
            state = QValidator::Invalid;
        else if (num >= m_min && num <= m_max)
            state = QValidator::Acceptable;
        else if (num > m_max)
            state = QValidator::Invalid;
        else
            state = QValidator::Intermediate;
    }

    if (state != QValidator::Acceptable)
        num = m_min;

    return num;
}

    
} // namespace propertyguizeug
