
#include <string>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/PropertySerializer.h>
#include <reflectionzeug/PropertyDeserializer.h>
#include <propertyguizeug/PropertyBrowser.h>

#include "libzeug-version.h"

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
    QApplication::setApplicationName("propertygui-example");
    QApplication::setOrganizationName(META_AUTHOR_ORGANIZATION);

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
        
    visible->setOption("tooltip", "Opens and closes the example window.");

    PropertyGroup * size = settings->addGroup("Size");

    auto * width = size->addProperty<int>("Width",
        [widget] () -> int {
            return widget->width();
        },
        [widget] (const int & width) {
            widget->resize(width, widget->height());
        });
    
    width->setOption("minimum", widget->minimumWidth());
    width->setOption("maximum", widget->maximumWidth());
    width->setOption("suffix", " pixel");

    auto * height = size->addProperty<int>("Height",
        [widget] () -> int {
            return widget->height();
        },
        [widget] (const int & height) {
            widget->resize(widget->width(), height);
        });

    height->setOption("minimum", widget->minimumHeight());
    height->setOption("maximum", widget->maximumHeight());
    height->setOption("suffix", " pixel");

    auto * aspect = size->addProperty<float>("Aspect",
        [widget] () -> float {
            return static_cast<float>(widget->width()) / widget->height();
        },
        [widget] (const float & aspect) {
            int width = static_cast<int>(aspect * widget->height());
            widget->resize(width, widget->height());
        });
    aspect->setOption("step", 0.1f);
    aspect->setOption("suffix", " w/h");
    aspect->setOption("precision", 4);
    
    const char * sizeTitles[] = { "Width", "Height" };
    
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
                width->setOption("minimum", size);
                break;
            case 1:
                widget->setMinimumHeight(size);
                height->setOption("minimum", size);
                
            }
        });
    
    minimumSize->setOption("title", "Minimum Size");
    for (size_t i = 0; i < minimumSize->count(); ++i)
        minimumSize->at(i)->setOption("title", sizeTitles[i]);

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
                width->setOption("maximum", size);
                break;
            case 1:
                widget->setMaximumHeight(size);
                height->setOption("maximum", size);
            }
        });
      
    maximumSize->setOption("title", "Maximum Size");
    for (size_t i = 0; i < maximumSize->count(); ++i)
        maximumSize->at(i)->setOption("title", sizeTitles[i]);

    

    auto * windowTitle = settings->addProperty<std::string>("windowTitle",
        [widget]() {
            return widget->windowTitle().toStdString();
        },
        [widget](const std::string & title) {
            widget->setWindowTitle(QString::fromStdString(title));
        });

    windowTitle->setOption("title", "Window Title");

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

    backgroundColor->setOption("title", "Background Color");
    backgroundColor->setOption("tooltip", "Sets the background color of the example window.");

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
    filePath->setOption("uniqueidentifier", "settings/filePath");
    filePath->setOption("tooltip", "A file path with no meaning.");

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
