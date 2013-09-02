
#include <QWidget>
#include "propertyguizeug/WidgetBuilder.h"

namespace propertyguizeug {

WidgetBuilder::WidgetBuilder()
:   AbstractPropertyVisitor()
{
}

WidgetBuilder::~WidgetBuilder()
{
}
    
QWidget * WidgetBuilder::build(PropertyGroup & group)
{
    return new QWidget();
}
    
void WidgetBuilder::visit(Property<bool> & property)
{

}

void WidgetBuilder::visit(Property<int> & property)
{

}

void WidgetBuilder::visit(Property<unsigned int> & property)
{

}

void WidgetBuilder::visit(Property<long> & property)
{

}

void WidgetBuilder::visit(Property<unsigned long> & property)
{

}

void WidgetBuilder::visit(Property<char> & property)
{

}

void WidgetBuilder::visit(Property<unsigned char> & property)
{

}

void WidgetBuilder::visit(Property<float> & property)
{

}

void WidgetBuilder::visit(Property<double> & property)
{

}

void WidgetBuilder::visit(Property<std::string> & property)
{

}

void WidgetBuilder::visit(Property<Color> & property)
{

}

void WidgetBuilder::visit(Property<FilePath> & property)
{

}

void WidgetBuilder::visit(Property<std::vector<bool>> & property)
{

}

void WidgetBuilder::visit(Property<std::vector<int>> & property)
{

}

void WidgetBuilder::visit(Property<std::vector<float>> & property)
{

}

void WidgetBuilder::visit(Property<std::vector<double>> & property)
{

}

void WidgetBuilder::visit(PropertyGroup & property)
{

}

} // namespace