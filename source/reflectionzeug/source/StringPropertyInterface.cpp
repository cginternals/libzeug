
#include <reflectionzeug/PropertyCategoryVisitor.h>
#include <reflectionzeug/StringPropertyInterface.h>

namespace reflectionzeug
{

void StringPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<StringPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

bool StringPropertyInterface::hasChoices() const
{
    return !m_choices.empty();
}

void StringPropertyInterface::addChoice(const std::string & string)
{
    m_choices.push_back(string);
    this->choicesChanged(m_choices);
}

const std::vector<std::string> & StringPropertyInterface::choices() const
{
    return m_choices;
}

void StringPropertyInterface::setChoices(const std::vector<std::string> & choices)
{
    m_choices = choices;
    this->choicesChanged(m_choices);
}

void StringPropertyInterface::clearChoices()
{
    m_choices.clear();
    this->choicesChanged(m_choices);
}


} // namespace reflectionzeug
