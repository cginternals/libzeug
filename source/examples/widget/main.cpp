#include <iostream>

#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

#include <widgetzeug/ColorGradientWidget.h>

#include "libzeug-version.h"

using namespace widgetzeug;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("widgetzeug-example");
    QApplication::setOrganizationName(META_AUTHOR_ORGANIZATION);
    QApplication::setApplicationVersion(META_VERSION);
    
    QWidget mainWidget;
    
    auto gradient = ColorGradient::fromList(
        { { 30, 136, 229 }, { 47, 120, 108 }, { 242, 223, 149 } },
        ColorGradientType::Discrete, 8);

    auto widget = new ColorGradientWidget{gradient};
    
    auto button = new QPushButton{&mainWidget};
    button->setText("Choose Gradient");
    
    auto label = new QLabel{&mainWidget};
    label->setScaledContents(true);
    label->setMinimumHeight(30);
    
    QObject::connect(button, &QPushButton::pressed,
        [widget] ()
        {
            widget->show();
        });
    
    QObject::connect(widget, &QDialog::accepted,
        [widget, label] ()
        {
            auto gradient = widget->gradient();
            auto image = gradient.image(100);
            label->setPixmap(QPixmap::fromImage(image));
        });
    
    auto layout = new QVBoxLayout{&mainWidget};
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->addWidget(button);
    layout->addWidget(label);
    
    mainWidget.show();

    auto result = a.exec();
    return result;
}
