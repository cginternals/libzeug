#include <propertyguizeug/ColorEditor.h>

#include <QApplication>
#include <QColor>
#include <QColorDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QRegExpValidator>
#include <QStyleOptionViewItem>

#include <reflectionzeug/ColorPropertyInterface.h>

#include <propertyguizeug/ColorButton.h>

using namespace reflectionzeug;

namespace 
{

QColor toQColor(const Color & color)
{
    return {color.red(), color.green(), color.blue(), color.alpha()};
}

Color toColor(const QColor & color)
{
    return {color.red(), color.green(), color.blue(), color.alpha()};
}

} // namespace

namespace propertyguizeug
{

void ColorEditor::paint(
    QPainter * painter, 
    const QStyleOptionViewItem & option, 
    ColorPropertyInterface & property)
{
    auto color = property.toColor();
    auto qcolor = toQColor(color);

    const auto metrics = option.widget->fontMetrics();
    const auto buttonSize = ColorButton::sizeFromFontHeight(metrics.height(), false);
    auto buttonRect = QRect{option.rect.topLeft(), buttonSize};
    buttonRect.moveCenter({buttonRect.center().x(), option.rect.center().y()});
    const auto topLeft = buttonRect.topLeft();

    ColorButton::paint(painter, topLeft, qcolor);

    auto rect = option.rect;
    rect.setLeft(option.rect.left() + 
                 buttonSize.width() + 4);

    auto widget = option.widget;
    auto style = widget ? widget->style() : QApplication::style();
    style->drawItemText(
        painter,
        rect,
        Qt::AlignVCenter,
        option.palette,
        true,
        QString::fromStdString(property.toString()),
        QPalette::Text);
}
                      
ColorEditor::ColorEditor(ColorPropertyInterface * property, QWidget * parent)
:   PropertyEditor{parent}
,   m_property{property}
{
    Color color = m_property->toColor();
    QColor qcolor = toQColor(color);
    
    m_lineEdit = new QLineEdit{this};
    m_lineEdit->setText(QString::fromStdString(m_property->toString()));
    
    m_button = new ColorButton{this, qcolor};
    
    boxLayout()->setSpacing(2);
    addWidget(m_button);
    addWidget(m_lineEdit);
    setFocusProxy(m_lineEdit);

    auto validator = new QRegExpValidator{QRegExp{"#[0-9A-Fa-f]{8}"}, this};
    m_lineEdit->setValidator(validator);
    
    this->connect(m_button, &ColorButton::pressed, this, &ColorEditor::openColorPicker);
    this->connect(m_lineEdit, &QLineEdit::editingFinished, this, &ColorEditor::parseColor);
}
    
void ColorEditor::openColorPicker()
{
    auto qcolor = QColorDialog::getColor(
        qColor(),
        m_button,
        "Choose Color",
        QColorDialog::ShowAlphaChannel);
        
    if (qcolor.isValid())
        this->setQColor(qcolor);
}

void ColorEditor::parseColor()
{
    QString text = m_lineEdit->text();
    text.remove('#');

    Color color(text.toUInt(0, 16));
    this->setColor(color);
}
    
QColor ColorEditor::qColor() const
{
    return toQColor(m_property->toColor());
}

void ColorEditor::setQColor(const QColor & qcolor)
{
    Color color = toColor(qcolor);
    m_property->fromColor(color);
    m_button->setColor(qcolor);
    m_lineEdit->setText(QString::fromStdString(m_property->toString()));
}

void ColorEditor::setColor(const Color & color)
{
    QColor qcolor = toQColor(color);
    m_property->fromColor(color);
    m_button->setColor(qcolor);
    m_lineEdit->setText(QString::fromStdString(m_property->toString()));
}

} // namespace propertyguizeug
