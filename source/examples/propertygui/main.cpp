
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/PropertySerializer.h>
#include <reflectionzeug/PropertyDeserializer.h>
#include <propertyguizeug/PropertyBrowser.h>

#include "Switch.h"

#ifdef WIN32
#define SETTINGS_PATH ".\\data\\propertygui.ini"
#else
#define SETTINGS_PATH "./data/propertygui.ini"
#endif


using namespace reflectionzeug;
using namespace propertyguizeug;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("hpicgs_libzeug");
    
    auto * widget = new QWidget();
    widget->setMinimumWidth(200);
    widget->setMaximumWidth(640);
    widget->setMinimumHeight(200);
    widget->setMaximumHeight(460);
    widget->setWindowTitle("Property Example");
    widget->setAutoFillBackground(true);

    auto * settings = new PropertyGroup("Settings");

    auto * visible = settings->addProperty<bool>("Visible",
        [widget]() {
            return widget->isVisible();
        },
        [widget](const bool & b) {
            widget->setVisible(b);
        });

    PropertyGroup * size = settings->addGroup("Size");

    auto * width = size->addProperty<int>("Width",
        [widget]() {
            return widget->width();
        },
        [widget](const int & width) {
            widget->resize(width, widget->height());
        });

    width->setRange(widget->minimumWidth(), widget->maximumWidth());

    auto * height = size->addProperty<int>("Height",
        [widget]() {
            return widget->height();
        },
        [widget](const int & height) {
            widget->resize(widget->width(), height);
        });

    height->setRange(widget->minimumHeight(), widget->maximumHeight());

    auto * minimumSize = size->addProperty<std::array<int, 2>>("minimumSize",
        [widget] () -> std::array<int, 2> {
            return { {widget->minimumWidth(), widget->minimumHeight()} };
        },
        [widget, width, height] (const std::array<int, 2> & size) {
            widget->setMinimumSize(QSize(size[0], size[1]));
            width->setMinimum(size[0]);
            height->setMinimum(size[1]);
        });

    minimumSize->setTitle("Minimum Size");

    auto * maximumSize = size->addProperty<std::array<int, 2>>("maximumSize",
        [widget]() -> std::array<int, 2> {
            return { {widget->maximumWidth(), widget->maximumHeight()} };
        },
        [widget, width, height] (const std::array<int, 2> & size) {
            widget->setMaximumSize(QSize(size[0], size[1]));
            width->setMaximum(size[0]);
            height->setMaximum(size[1]);
        });

    maximumSize->setTitle("Maximum Size");

    auto * windowTitle = settings->addProperty<std::string>("windowTitle",
        [widget]() {
            return widget->windowTitle().toStdString();
        },
        [widget](const std::string & title) {
            widget->setWindowTitle(QString::fromStdString(title));
        });

    windowTitle->setTitle("Window Title");

    auto * backgroundColor = settings->addProperty<Color>("backgroundColor",
        [widget]() {
            QColor qcolor = widget->palette().color(QPalette::Window);
            return Color(qcolor.red(), qcolor.green(), qcolor.blue(), qcolor.alpha());
        },
        [widget](const Color & color) {
            QColor qcolor(color.red(), color.green(), color.blue(), color.alpha());
            QPalette palette;
            palette.setColor(QPalette::Window, qcolor);
            widget->setPalette(palette);
        });

    backgroundColor->setTitle("Background Color");

    auto * cursorProperty = settings->addProperty<Qt::CursorShape>("Cursor",
        [widget] () 
        {
            return widget->cursor().shape();
        },
        [widget] (const Qt::CursorShape & shape) 
        {
            widget->setCursor(QCursor(shape));
        });

    cursorProperty->setStrings({
        { Qt::PointingHandCursor, "Pointing Hand Cursor" },
        { Qt::BusyCursor, "Busy Cursor" },
        { Qt::ArrowCursor, "Arrow Cursor" },
        { Qt::WaitCursor, "Wait Cursor" }
    });

    settings->addProperty<Switch>("switch", Switch(true));

    PropertyDeserializer deserializer;
    deserializer.deserialize(*settings, SETTINGS_PATH);

    auto * browser = new PropertyBrowser(settings);
    browser->show();

    int result = a.exec();

    PropertySerializer serializer;
    serializer.serialize(*settings, SETTINGS_PATH);

    delete settings;
    delete browser;
    delete widget;
    
    return result;
}
