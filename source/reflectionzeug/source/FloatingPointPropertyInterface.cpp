
#include <reflectionzeug/PropertyCategoryVisitor.h>
#include <reflectionzeug/FloatingPointPropertyInterface.h>

namespace reflectionzeug
{

FloatingPointPropertyInterface::~FloatingPointPropertyInterface()
{

}

void FloatingPointPropertyInterface::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<FloatingPointPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
    {
        AbstractValueProperty::accept(visitor, warn);
        return;
    }

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
