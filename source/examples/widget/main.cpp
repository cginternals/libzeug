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

    auto gradient = ColorGradient::fromList({ { 30, 136, 229 }, { 47, 120, 108 }, { 242, 223, 149 } }, ColorGradientType::Discrete);
    
    ColorGradientWidget widget{gradient};

    widget.show();

    auto result = a.exec();
    return result;
}
