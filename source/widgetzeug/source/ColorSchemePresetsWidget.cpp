#include <widgetzeug/ColorSchemePresetsWidget.h>

#include <cassert>

#include <QMultiMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QWheelEvent>
#include <QFile>
#include <QScreen>
#include <QScrollBar>
#include <QDebug>
#include <QWindow>

#include <widgetzeug/ColorScheme.h>

#include "ui_ColorSchemePresetsWidget.h"
#include "ColorSchemeGraphicsItem.h"
#include "ColorSchemeGraphicsView.h"


namespace widgetzeug
{

ColorSchemePresetsWidget::ColorSchemePresetsWidget(QWidget * parent)
:   QWidget(parent)
,   m_ui(new Ui_ColorSchemePresetWidget)
{
    m_ui->setupUi(this);
    setClassesFilter(m_ui->classesSpinBox->value());

    m_ui->deficiencyComboBox->addItem("None",        ColorScheme::None);
    m_ui->deficiencyComboBox->addItem("Grayscale",   ColorScheme::Grayscale);
    m_ui->deficiencyComboBox->addItem("Protanope",   ColorScheme::Protanope);
    m_ui->deficiencyComboBox->addItem("Deuteranope", ColorScheme::Deuteranope);
    m_ui->deficiencyComboBox->addItem("Tritanope",   ColorScheme::Tritanope);

    connect(m_ui->graphicsView, &ColorSchemeGraphicsView::selectedChanged,
            this, &ColorSchemePresetsWidget::selectedChanged);
            
    connect(m_ui->graphicsView, &ColorSchemeGraphicsView::selectedChanged,
            m_ui->colorSchemePreview, &SingleColorSchemeGraphicsView::setScheme);
}

ColorSchemePresetsWidget::~ColorSchemePresetsWidget()
{
}

ColorSchemePresetsWidget * ColorSchemePresetsWidget::fromJson(QFile & file, QWidget * parent)
{
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;

    const QString json = QString::fromUtf8(file.readAll());
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject groups = doc.object();

    ColorSchemePresetsWidget * widget = new ColorSchemePresetsWidget(parent);

    QMultiMap<int, QString> indexedCategories;
    
    static const QString CATEGORIE_INDEX("categorie-index");

    for (const QString & group : groups.keys())
    {
        QJsonObject schemes = groups[group].toObject();
        const int index = schemes.value(CATEGORIE_INDEX).toInt();

        indexedCategories.insertMulti(index, group);
    }
    for (const int index : indexedCategories.keys())
        for (const QString & group : indexedCategories.values(index))
        {
            QJsonObject schemes = groups[group].toObject();
            schemes.take(CATEGORIE_INDEX);
            for (const QString & identifier : schemes.keys())
                widget->insertScheme(group, ColorScheme::fromJson(identifier, schemes));
        }

	widget->ensureDefaultSelection();

    return widget;
}

void ColorSchemePresetsWidget::createGroup(const QString & identifier)
{
    m_ui->graphicsView->createGroup(identifier);
}

void ColorSchemePresetsWidget::insertScheme(const QString & group, ColorScheme * scheme)
{
    m_ui->graphicsView->insertScheme(group, scheme);
}

void ColorSchemePresetsWidget::setSelected(ColorScheme * scheme)
{
    m_ui->graphicsView->setSelected(scheme);
}

ColorScheme * ColorSchemePresetsWidget::selected()
{
    return m_ui->graphicsView->selected();
}

void ColorSchemePresetsWidget::setTypeFilter(const ColorScheme::ColorSchemeTypes & types)
{
    m_ui->graphicsView->setTypeFilter(types);
}

const ColorScheme::ColorSchemeTypes & ColorSchemePresetsWidget::typeFilter() const
{
    return m_ui->graphicsView->typeFilter();
}

void ColorSchemePresetsWidget::setClassesFilter(int classes)
{
    m_ui->graphicsView->setClassesFilter(classes);
    m_ui->colorSchemePreview->setClasses(classes);
}

int ColorSchemePresetsWidget::classesFilter() const
{
    return m_ui->graphicsView->classesFilter();
}

void ColorSchemePresetsWidget::setDeficiency(ColorScheme::ColorVisionDeficiency deficiency)
{
    int index = m_ui->deficiencyComboBox->findData(deficiency);

    m_ui->deficiencyComboBox->blockSignals(true);
    m_ui->deficiencyComboBox->setCurrentIndex(index);
    m_ui->deficiencyComboBox->blockSignals(false);

    m_ui->graphicsView->setDeficiency(deficiency);
    m_ui->colorSchemePreview->setDeficiency(deficiency);
}

ColorScheme::ColorVisionDeficiency ColorSchemePresetsWidget::deficiency() const
{
    return m_ui->graphicsView->deficiency();
}

void ColorSchemePresetsWidget::ensureDefaultSelection()
{
	m_ui->graphicsView->ensureDefaultSelection();
}

void ColorSchemePresetsWidget::on_sequentialCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked)
        setTypeFilter(typeFilter() | ColorScheme::Sequential);
    else    
        setTypeFilter(typeFilter() ^ ColorScheme::Sequential);
	
	ensureDefaultSelection();
}

void ColorSchemePresetsWidget::on_divergingCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked)
        setTypeFilter(typeFilter() | ColorScheme::Diverging);
    else
        setTypeFilter(typeFilter() ^ ColorScheme::Diverging);

	ensureDefaultSelection();
}

void ColorSchemePresetsWidget::on_qualitativeCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked)
        setTypeFilter(typeFilter() | ColorScheme::Qualitative);
    else
        setTypeFilter(typeFilter() ^ ColorScheme::Qualitative);

	ensureDefaultSelection();
}

void ColorSchemePresetsWidget::on_classesSpinBox_valueChanged(int value)
{
    setClassesFilter(value);
}

void ColorSchemePresetsWidget::on_deficiencyComboBox_currentIndexChanged(int index)
{
    setDeficiency(static_cast<ColorScheme::ColorVisionDeficiency>(m_ui->deficiencyComboBox->itemData(index).toInt()));
}

} // namespace widgetzeug
