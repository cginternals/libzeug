
#include <widgetzeug/ColorSchemePresetsWidget.h>

#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/ColorSchemePresets.h>

#include "ui_ColorSchemePresetsWidget.h"

#include "ColorSchemeGraphicsItem.h"
#include "ColorSchemeGraphicsView.h"


namespace widgetzeug
{

ColorSchemePresetsWidget::ColorSchemePresetsWidget(QWidget * parent)
:  QWidget(parent)
, m_ui{ new Ui_ColorSchemePresetWidget }
{
    initialize();
}

ColorSchemePresetsWidget::ColorSchemePresetsWidget(const ColorSchemePresets & presets, QWidget * parent)
: QWidget(parent)
, m_ui{ new Ui_ColorSchemePresetWidget }
{
    initialize();
    setPresets(presets);
}

ColorSchemePresetsWidget::~ColorSchemePresetsWidget()
{
    delete m_ui;
}

void ColorSchemePresetsWidget::setPresets(const ColorSchemePresets & presets)
{
    m_ui->graphicsView->clear();

	ColorScheme::ColorSchemeTypes types = ColorScheme::Unknown;

    for (const auto category : presets)
		for (const auto scheme : *category)
		{
			insertScheme(category->identifier(), *scheme);
			types |= scheme->type();
		}

	m_ui->sequentialCheckBox->setEnabled(types.testFlag(ColorScheme::Sequential));
	m_ui->divergingCheckBox->setEnabled(types.testFlag(ColorScheme::Diverging));
	m_ui->qualitativeCheckBox->setEnabled(types.testFlag(ColorScheme::Qualitative));

	m_ui->graphicsView->update();
}

void ColorSchemePresetsWidget::initialize()
{
    m_ui->setupUi(this);
    setClassesFilter(m_ui->classesSpinBox->value());

    for (auto deficiency : ColorScheme::s_deficiencies.keys())
        m_ui->deficiencyComboBox->addItem(ColorScheme::s_deficiencies[deficiency]
            , static_cast<deficiency_type>(deficiency));

    connect(m_ui->graphicsView, &ColorSchemeGraphicsView::selectedChanged
        , this, &ColorSchemePresetsWidget::selectedChanged);
}

void ColorSchemePresetsWidget::createGroup(const QString & identifier)
{
    m_ui->graphicsView->createGroup(identifier);
}

void ColorSchemePresetsWidget::insertScheme(const QString & group, const ColorScheme & scheme)
{
    m_ui->graphicsView->insertScheme(group, &scheme);

    m_ui->classesSpinBox->setMinimum(m_ui->graphicsView->minClasses());
    m_ui->classesSpinBox->setMaximum(m_ui->graphicsView->maxClasses());
}

void ColorSchemePresetsWidget::setSelected(const ColorScheme & scheme)
{
    m_ui->graphicsView->setSelected(&scheme);
}

const ColorScheme * ColorSchemePresetsWidget::selected()
{
    return m_ui->graphicsView->selected();
}

void ColorSchemePresetsWidget::setTypeFilter(const ColorScheme::ColorSchemeTypes & types)
{
    m_ui->graphicsView->setTypeFilter(types);
}

ColorScheme::ColorSchemeTypes ColorSchemePresetsWidget::typeFilter() const
{
    return m_ui->graphicsView->typeFilter();
}

void ColorSchemePresetsWidget::setClassesFilter(const uint classes)
{
    m_ui->graphicsView->setClassesFilter(classes);
}

uint ColorSchemePresetsWidget::classesFilter() const
{
    return m_ui->graphicsView->classesFilter();
}

void ColorSchemePresetsWidget::setDeficiency(const ColorVisionDeficiency deficiency)
{
    int index = m_ui->deficiencyComboBox->findData(static_cast<deficiency_type>(deficiency));

    m_ui->deficiencyComboBox->blockSignals(true); 
    m_ui->deficiencyComboBox->setCurrentIndex(index);
    m_ui->deficiencyComboBox->blockSignals(false);

    m_ui->graphicsView->setDeficiency(deficiency);
}

ColorVisionDeficiency ColorSchemePresetsWidget::deficiency() const
{
    return m_ui->graphicsView->deficiency();
}

void ColorSchemePresetsWidget::on_sequentialCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked)
        setTypeFilter(typeFilter() | ColorScheme::Sequential);
    else    
        setTypeFilter(typeFilter() ^ ColorScheme::Sequential);
}

void ColorSchemePresetsWidget::on_divergingCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked)
        setTypeFilter(typeFilter() | ColorScheme::Diverging);
    else
        setTypeFilter(typeFilter() ^ ColorScheme::Diverging);
}

void ColorSchemePresetsWidget::on_qualitativeCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked)
        setTypeFilter(typeFilter() | ColorScheme::Qualitative);
    else
        setTypeFilter(typeFilter() ^ ColorScheme::Qualitative);
}

void ColorSchemePresetsWidget::on_classesSpinBox_valueChanged(int value)
{
    setClassesFilter(value);
}

void ColorSchemePresetsWidget::on_deficiencyComboBox_currentIndexChanged(int index)
{
    setDeficiency(static_cast<ColorVisionDeficiency>(m_ui->deficiencyComboBox->itemData(index).toInt()));
}

} // namespace widgetzeug
