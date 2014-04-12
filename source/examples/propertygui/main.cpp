
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

    settings->addProperty<bool>("Visible",
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
        [widget] (size_t i) -> int {
            switch (i) 
            {
                case 0:
                    return widget->minimumWidth();
                case 1:
                    return widget->minimumHeight();
            }
        },
        [widget, width, height] (size_t i, int value) {
            switch (i) 
            {
                case 0:
                    widget->setMinimumWidth(value);
                    width->setMinimum(value);
                case 1:
                    widget->setMinimumHeight(value);
                    height->setMinimum(value);
            }
        });

    minimumSize->setTitle("Minimum Size");

    auto * maximumSize = size->addProperty<std::array<int, 2>>("maximumSize",
        [widget] (size_t i) -> int {
           switch (i) 
           {
               case 0:
                   return widget->maximumWidth();
               case 1:
                   return widget->maximumHeight();
           }
        },
        [widget, width, height] (size_t i, int value) {
           switch (i) 
           {
               case 0:
                   widget->setMaximumWidth(value);
                   width->setMaximum(value);
               case 1:
                   widget->setMaximumHeight(value);
                   height->setMaximum(value);
           }
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
    
    settings->addProperty<unsigned long long int>("unsigned_int", 12);
    
    auto prop = settings->addProperty<std::array<std::string, 2>>("float_array", { "ad", "ad" });

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
