#include <iostream>

#include <QApplication>

#include <widgetzeug/ColorGradientWidget.h>

#include "libzeug-version.h"

using namespace widgetzeug;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("widgetzeug-example");
    QApplication::setOrganizationName(META_AUTHOR_ORGANIZATION);
    QApplication::setApplicationVersion(META_VERSION);

    auto gradient = ColorGradient::fromList({ Qt::red, Qt::blue }, ColorGradientType::Linear);
    
    ColorGradientWidget widget{gradient};

    widget.show();

    auto result = a.exec();
    return result;
}
