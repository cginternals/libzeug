
#pragma once

#include <QAbstractSpinBox>

#include <propertyguizeug/propertyguizeug.h>


namespace propertyguizeug
{

class PROPERTYGUIZEUG_API ULongLongSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    
public:
    ULongLongSpinBox(QWidget * parent = nullptr);

    virtual void fixup(QString & input) const;
    virtual void stepBy(int steps);
    virtual QValidator::State validate(QString & input, int & pos) const;
    
    qulonglong value() const;
    void setValue(qulonglong value);
    
    qulonglong minimum() const;
    void setMinimum(qulonglong minimum);

    qulonglong maximum() const;
    void setMaximum(qulonglong maximum);
    
    qulonglong step() const;
    void setStep(qulonglong step);

    void setRange(qulonglong min,
                  qulonglong max);
    
signals:
    void valueChanged(qulonglong value);
    
protected slots:
    void onEditingFinished();

protected:
    virtual StepEnabled stepEnabled() const;
    
private:
    QString textFromValue(qulonglong value);
    qulonglong valueFromText(const QString & text);
    qulonglong validateAndInterpret(const QString & input, 
                                    int & pos, 
                                    QValidator::State & state) const;

private:
    qulonglong m_min;
    qulonglong m_max;
    qulonglong m_step;
    qulonglong m_value;
    
};
    
} // namespace propertyguizeug
