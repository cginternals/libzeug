
#pragma once

#include <QAbstractSpinBox>

#include <propertyguizeug/propertyguizeug.h>


namespace propertyguizeug
{

class PROPERTYGUIZEUG_API LongLongSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    
public:
    LongLongSpinBox(QWidget * parent = nullptr);

    virtual void fixup(QString & input) const;
    virtual void stepBy(int steps);
    virtual QValidator::State validate(QString & input, int & pos) const;
    
    long long value() const;
    void setValue(const long long & value);
    
    long long minimum() const;
    void setMinimum(const long long & minimum);

    long long maximum() const;
    void setMaximum(const long long & maximum);
    
    long long step() const;
    void setStep(const long long & step);

    void setRange(const long long & min,
                  const long long & max);
    
signals:
    void valueChanged(const long long & value);
    
protected slots:
    void onEditingFinished();

protected:
    virtual StepEnabled stepEnabled() const;
    
private:
    long long m_min;
    long long m_max;
    long long m_step;
    long long m_value;
    
};
    
} // namespace propertyguizeug
