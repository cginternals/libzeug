
#pragma once

#include <QAbstractSpinBox>

#include <propertyguizeug/propertyguizeug_api.h>


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
    
    qlonglong value() const;
    void setValue(qlonglong value);
    
    qlonglong minimum() const;
    void setMinimum(qlonglong minimum);

    qlonglong maximum() const;
    void setMaximum(qlonglong maximum);
    
    qlonglong step() const;
    void setStep(qlonglong step);

    void setRange(qlonglong min,
                  qlonglong max);

    const QString & prefix() const;
    void setPrefix(const QString & prefix);

    const QString & suffix() const;
    void setSuffix(const QString & suffix);
    
signals:
    void valueChanged(qlonglong value);
    
protected slots:
    void onEditingFinished();

protected:
    virtual StepEnabled stepEnabled() const;
    
private:
    void updateLineEditText();
    QString textFromValue(qlonglong value);
    qlonglong valueFromText(const QString & text);
    qlonglong validateAndInterpret(const QString & input, 
                                   int & pos, 
                                   QValidator::State & state) const;

private:
    qlonglong m_min;
    qlonglong m_max;
    qlonglong m_step;
    qlonglong m_value;
    QString m_prefix;
    QString m_suffix;
    
};
    
} // namespace propertyguizeug
