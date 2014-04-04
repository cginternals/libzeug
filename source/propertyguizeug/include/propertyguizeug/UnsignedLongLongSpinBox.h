
#pragma once

#include <QAbstractSpinBox>

#include <propertyguizeug/propertyguizeug.h>


namespace propertyguizeug
{

class PROPERTYGUIZEUG_API UnsignedLongLongSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    
public:
    UnsignedLongLongSpinBox(QWidget * parent = nullptr);

    virtual void fixup(QString & input) const;
    virtual void stepBy(int steps);
    virtual QValidator::State validate(QString & input, int & pos) const;
    
    unsigned long long value() const;
    void setValue(const unsigned long long & value);
    
    unsigned long long minimum() const;
    void setMinimum(const unsigned long long & minimum);

    unsigned long long maximum() const;
    void setMaximum(const unsigned long long & maximum);
    
    unsigned long long step() const;
    void setStep(const unsigned long long & step);

    void setRange(const unsigned long long & min,
                  const unsigned long long & max);
    
signals:
    void valueChanged(const unsigned long long & value);
    
protected slots:
    void onEditingFinished();

protected:
    virtual StepEnabled stepEnabled() const;
    
private:
    unsigned long long m_min;
    unsigned long long m_max;
    unsigned long long m_step;
    unsigned long long m_value;
    
};
    
} // namespace propertyguizeug
