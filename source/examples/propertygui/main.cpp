
#include <string>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
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
        [widget] () -> int {
            return widget->width();
        },
        [widget] (const int & width) {
            widget->resize(width, widget->height());
        });

    width->setRange(widget->minimumWidth(), widget->maximumWidth());

    auto * height = size->addProperty<int>("Height",
        [widget] () -> int {
            return widget->height();
        },
        [widget] (const int & height) {
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
            default:
                return -1;
            }
        },
        [widget, width, height] (size_t i, const int & size) {
            switch (i)
            {
            case 0:
                widget->setMinimumWidth(size);
                width->setMinimum(size);
                break;
            case 1:
                widget->setMinimumHeight(size);
                height->setMinimum(size);
            }
        });

    minimumSize->setTitle("Minimum Size");

    auto * maximumSize = size->addProperty<std::array<int, 2>>("maximumSize",
        [widget](size_t i) -> int {
            switch (i)
            {
            case 0:
                return widget->maximumWidth();
            case 1:
                return widget->maximumHeight();
            default:
                return -1;
            
            }
        },
        [widget, width, height] (size_t i, const int & size) {
            switch (i)
            {
            case 0:
                widget->setMaximumWidth(size);
                width->setMaximum(size);
                break;
            case 1:
                widget->setMaximumHeight(size);
                height->setMaximum(size);
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
    
    Property<FilePath> * filePath = settings->addProperty<FilePath>("filePath", "");
    filePath->setUniqueIdentifier("settings/filePath");

    QPushButton button("Add");

    QObject::connect(&button, &QAbstractButton::pressed, [settings] ()
        {
            static int i = 0;
            settings->addProperty<int>("_" + std::to_string(i++), 12);
        });
    
    button.show();

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
