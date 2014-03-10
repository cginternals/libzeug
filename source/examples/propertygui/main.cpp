
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/PropertySerializer.h>
#include <reflectionzeug/PropertyDeserializer.h>
#include <propertyguizeug/PropertyBrowser.h>

#include "PropertyExtension.h"

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

    auto * minimumSize = size->addProperty<std::vector<int>>("minimumSize",
        [widget]() {
            std::vector<int> range;
            range.push_back(widget->minimumWidth());
            range.push_back(widget->minimumHeight());
            return range;
        },
        [widget, width, height](const std::vector<int> & size) {
            widget->setMinimumSize(QSize(size[0], size[1]));
            width->setMinimum(size[0]);
            height->setMinimum(size[1]);
        });

    minimumSize->setTitle("Minimum Size");

    auto * maximumSize = size->addProperty<std::vector<int>>("maximumSize",
        [widget]() {
            std::vector<int> range;
            range.push_back(widget->maximumWidth());
            range.push_back(widget->maximumHeight());
            return range;
        },
        [widget, width, height](const std::vector<int> & size) {
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

    auto * cursor = settings->addProperty<std::string>("Cursor",
        [widget]() {
            switch (widget->cursor().shape()) {
                case Qt::PointingHandCursor:
                    return "Pointing Hand Cursor";
                case Qt::BusyCursor:
                    return "Busy Cursor";
                default:
                    return "Arrow Cursor";
            }
        },
        [widget](const std::string & string) {
            if (string == "Pointing Hand Cursor")
                widget->setCursor(Qt::PointingHandCursor);
            else if (string == "Busy Cursor")
                widget->setCursor(Qt::BusyCursor);
            else
                widget->setCursor(Qt::ArrowCursor);
        });

    settings->addProperty<NormalMode>("normalMode", NormalMode::Vertex);
    settings->addProperty<Switch>("switch", Switch(true));

    std::vector<std::string> choices;
    choices.push_back("Arrow Cursor");
    choices.push_back("Pointing Hand Cursor");
    choices.push_back("Busy Cursor");
    cursor->setChoices(choices);

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
