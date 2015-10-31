
#include <propertyguizeug/ColorEditor.h>

#include <cassert>

#include <QApplication>
#include <QColorDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QRegExpValidator>
#include <QStyleOptionViewItem>

#include <reflectionzeug/property/AbstractProperty.h>
#include <reflectionzeug/property/AbstractColorInterface.h>

#include <propertyguizeug/ColorButton.h>


using namespace reflectionzeug;


namespace
{


static QColor toQColor(AbstractColorInterface & property)
{
    int r, g, b, a;
    property.getRGBA(r, g, b, a);
    return QColor(r, g, b, a);
}


} // namespace


namespace propertyguizeug
{


void ColorEditor::paint(
    QPainter * painter, 
    const QStyleOptionViewItem & option, 
    AbstractColorInterface & property)
{
    // Get color
    QColor color = toQColor(property);

    // Get options
    const auto includeAlpha = dynamic_cast<AbstractProperty &>(property).option<bool>("alpha", true);

    // Adjust position
    const auto metrics = option.widget->fontMetrics();
    const auto buttonSize = ColorButton::sizeFromFontHeight(metrics.height());
    auto buttonRect = QRect{option.rect.topLeft(), buttonSize};
    buttonRect.moveCenter({buttonRect.center().x(), option.rect.center().y()});
    const auto topLeft = buttonRect.topLeft();

    // Paint color button
    ColorButton::paint(painter, topLeft, color);

    // Paint color text
    auto widget = option.widget;
    auto style = widget ? widget->style() : QApplication::style();

    auto rect = option.rect;
    rect.setLeft(option.rect.left() + 
                 buttonSize.width() + 4);

    style->drawItemText(
        painter,
        rect,
        Qt::AlignVCenter,
        option.palette,
        true,
        QString::fromStdString(property.toHexString(includeAlpha)),
        QPalette::Text);
}
                      
ColorEditor::ColorEditor(AbstractColorInterface * property, QWidget * parent)
:   PropertyEditor{parent}
,   m_includeAlpha{true}
,   m_property{property}
{
    auto colorProperty = dynamic_cast<AbstractProperty *>(property);

    assert(colorProperty != nullptr);

    m_includeAlpha = colorProperty->option<bool>("alpha", true);

    // Get color
    QColor color = toQColor(*m_property);

    // Create text edit field for the color value
    m_lineEdit = new QLineEdit{this};
    m_lineEdit->setText(QString::fromStdString(m_property->toHexString(m_includeAlpha)));

    // Create color button to open a color picker
    m_button = new ColorButton{this, color};

    // Add widgets
    boxLayout()->setSpacing(2);
    addWidget(m_button);
    addWidget(m_lineEdit);
    setFocusProxy(m_lineEdit);

    // Create text validator for color hex values
    auto hexRegex = m_includeAlpha ? "#[0-9A-Fa-f]{8}" : "#[0-9A-Fa-f]{6}";
    auto validator = new QRegExpValidator{QRegExp{hexRegex}, this};
    m_lineEdit->setValidator(validator);

    // Open color picker on button press
    this->connect(m_button, &ColorButton::pressed, this, &ColorEditor::openColorPicker);

    // Update color value when text field has been edited
    this->connect(m_lineEdit, &QLineEdit::editingFinished, this, &ColorEditor::parseColor);

    // Update widgets when property value has changed
    m_propertyChangedConnection = dynamic_cast<AbstractProperty *>(m_property)->changed.connect(
        [this] ()
        {
            QColor color = toQColor(*m_property);
            m_button->setColor(color);
            m_lineEdit->setText(QString::fromStdString(m_property->toHexString(m_includeAlpha)));
        } );
}

ColorEditor::~ColorEditor()
{
}
    
void ColorEditor::openColorPicker()
{
    auto options = m_includeAlpha ? QColorDialog::ShowAlphaChannel : QColorDialog::ColorDialogOptions();
    
    auto qcolor = QColorDialog::getColor(
        toQColor(*m_property),
        m_button,
        "Choose Color",
        options);
        
    if (qcolor.isValid()) {
        this->setQColor(qcolor);
    }
}

void ColorEditor::parseColor()
{
    QString text = m_lineEdit->text();

    if (m_property->fromHexString(text.toStdString())) {
        QColor qcolor = toQColor(*m_property);
        m_button->setColor(qcolor);
    }
}

void ColorEditor::setQColor(const QColor & qcolor)
{
    m_property->setRGBA(qcolor.red(), qcolor.green(), qcolor.blue(), qcolor.alpha());
    m_button->setColor(qcolor);
    m_lineEdit->setText(QString::fromStdString(m_property->toHexString(m_includeAlpha)));
}


} // namespace propertyguizeug
