
#include <QHBoxLayout>
#include <QColorDialog>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
#include <QLabel>
#include <propertyguizeug/ColorEditor.h>

namespace propertyguizeug {

ColorEditor::ColorEditor(Property<Color> * property, QWidget * parent)
:   QWidget(parent)
,   m_property(property)
{
    QHBoxLayout * layout = new QHBoxLayout(this);
    QPushButton * button = new QPushButton("…", this);
    QLabel * label = new QLabel(this);
    QPixmap pixmap(16,16);
    const Color & color = property->value();
    pixmap.fill(QColor(color.red(), color.green(), color.blue(), color.alpha()));
    label->setPixmap(pixmap);
    this->connect(button, &QPushButton::clicked,
                  [this, label]() {
                      QColor color = QColorDialog::getColor();
                      m_property->setValue(Color(color.red(), color.green(), color.blue(), color.alpha()));
                      QPixmap pixmap(16,16);
                      pixmap.fill(color);
                      label->setPixmap(pixmap);
                  });
    
    layout->addWidget(label);
    layout->addWidget(button);
    
}

ColorEditor::~ColorEditor()
{
}

} // namespace
