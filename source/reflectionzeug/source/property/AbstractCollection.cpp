
#include <reflectionzeug/property/AbstractCollection.h>
#include <reflectionzeug/property/AbstractProperty.h>


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
        // Get property
        AbstractProperty * prop = at(i);

        // Visit property
        prop->accept(visitor);

        // If it is a collection, visit collection recursively
        AbstractCollection * collection = dynamic_cast<AbstractCollection *>(prop);
        if (collection) {
            collection->acceptRecursive(visitor);
        }
    }
}


} // namespace reflectionzeug
