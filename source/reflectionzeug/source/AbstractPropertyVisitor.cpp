
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/Property.h>

#include <reflectionzeug/AbstractPropertyVisitor.h>

namespace reflectionzeug
{

AbstractPropertyVisitor::AbstractPropertyVisitor()
{
    registerTypeHandler(
        static_cast<void(AbstractPropertyVisitor::*)(Property<bool> &)>(&AbstractPropertyVisitor::visit), this);
    
    registerTypeHandler(
        static_cast<void(AbstractPropertyVisitor::*)(Property<int> &)>(&AbstractPropertyVisitor::visit), this);

    registerTypeHandler(
        static_cast<void(AbstractPropertyVisitor::*)(Property<double> &)>(&AbstractPropertyVisitor::visit), this);

    registerTypeHandler(
        static_cast<void(AbstractPropertyVisitor::*)(Property<std::string> &)>(&AbstractPropertyVisitor::visit), this);

    registerTypeHandler(
        static_cast<void(AbstractPropertyVisitor::*)(Property<Color> &)>(&AbstractPropertyVisitor::visit), this);

    registerTypeHandler(
        static_cast<void(AbstractPropertyVisitor::*)(Property<FilePath> &)>(&AbstractPropertyVisitor::visit), this);

    registerTypeHandler(
        static_cast<void(AbstractPropertyVisitor::*)(Property<std::vector<bool>> &)>(&AbstractPropertyVisitor::visit), this);

    registerTypeHandler(
        static_cast<void(AbstractPropertyVisitor::*)(Property<std::vector<int>> &)>(&AbstractPropertyVisitor::visit), this);

    registerTypeHandler(
        static_cast<void(AbstractPropertyVisitor::*)(Property<std::vector<double>> &)>(&AbstractPropertyVisitor::visit), this);

    registerTypeHandler(
        static_cast<void(AbstractPropertyVisitor::*)(Property<std::set<int>> &)>(&AbstractPropertyVisitor::visit), this);

}
    
void AbstractPropertyVisitor::handle(ValueProperty & property)
{
    const std::type_index type(typeid(property));
    
    if (m_functors.count(type) == 0)
    {
        std::cout << "Could not visit not registered property." << std::endl;
        return;
    }
    
    m_functors.at(type)(property);
}

} // namespace reflectionzeug
