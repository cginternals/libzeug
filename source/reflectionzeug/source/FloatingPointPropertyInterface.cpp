
#include <reflectionzeug/PropertyCategoryVisitor.h>
#include <reflectionzeug/FloatingPointPropertyInterface.h>

namespace reflectionzeug
{

FloatingPointPropertyInterface::~FloatingPointPropertyInterface()
{

}

void FloatingPointPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<FloatingPointPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
