
#include <widgetzeug/ColorSchemeWidget.h>

#include <QDebug>

#include <widgetzeug/ColorScheme.h>


#include "ui_ColorSchemeWidget.h"


namespace widgetzeug
{

ColorSchemeWidget::ColorSchemeWidget(QWidget * parent)
: m_ui{ new Ui_ColorSchemeWidget() }
, m_scheme{ nullptr }
{
    m_ui->setupUi(this);
    setClasses(5);
}

ColorSchemeWidget::~ColorSchemeWidget()
{
    delete m_ui;
}

void ColorSchemeWidget::setScheme(const ColorScheme * scheme)
{
    if (scheme == m_scheme)
        return;

    m_scheme = scheme;

    m_ui->schemeLabel->setScheme(scheme);

    setEnabled(m_scheme != nullptr);
    if (!m_scheme)
        return;

    // these might trigger value change?
    m_ui->classesSpinBox->setMinimum(scheme->minClasses());
    m_ui->classesSpinBox->setMaximum(scheme->maxClasses());
}

void ColorSchemeWidget::setClasses(uint classes)
{
    m_ui->classesSpinBox->blockSignals(true);
    m_ui->classesSpinBox->setValue(classes);
    m_ui->classesSpinBox->blockSignals(false);

    m_ui->schemeLabel->setClasses(classes);
}
uint ColorSchemeWidget::classes() const
{
    return m_ui->classesSpinBox->value();
}

void ColorSchemeWidget::setInverted(const bool invert)
{
    m_ui->invertedCheckBox->blockSignals(true);
    m_ui->invertedCheckBox->setChecked(invert);
    m_ui->invertedCheckBox->blockSignals(false);

    m_ui->schemeLabel->setInverted(invert);
}
bool ColorSchemeWidget::inverted() const
{
    return m_ui->invertedCheckBox->isChecked();
}

void ColorSchemeWidget::on_classesSpinBox_valueChanged(int value)
{
    m_ui->schemeLabel->setClasses(value);
    emit classesChanged(value);
}

void ColorSchemeWidget::on_invertedCheckBox_toggled(bool checked)
{
    m_ui->schemeLabel->setInverted(checked);
    emit invertedChanged(checked);
}

} // namespace widgetzeug
