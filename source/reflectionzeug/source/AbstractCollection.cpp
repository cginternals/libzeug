
#include <reflectionzeug/AbstractCollection.h>
#include <reflectionzeug/AbstractValue.h>


namespace reflectionzeug
{


AbstractCollection::AbstractCollection()
{
}

AbstractCollection::~AbstractCollection()
{
}

void AbstractCollection::acceptRecursive(AbstractVisitor * visitor)
{
    // Visit all values of the collection
    for (size_t i=0; i<count(); i++) {
        // Get value
        AbstractValue * value = at(i);

        // Visit value
        value->accept(visitor);

        // If it is a collection, visit collection recursively
        AbstractCollection * collection = dynamic_cast<AbstractCollection *>(value);
        if (collection) {
            collection->acceptRecursive(visitor);
        }
    }
}


} // namespace reflectionzeug
