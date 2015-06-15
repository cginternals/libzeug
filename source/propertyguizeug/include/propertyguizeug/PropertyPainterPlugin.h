#pragma once

#include <reflectionzeug/property/AbstractVisitor.h>

#include <propertyguizeug/PropertyPainter.h>

namespace propertyguizeug
{

class AbstractPropertyPainterPlugin : public virtual reflectionzeug::AbstractVisitor
{
public:
    virtual ~AbstractPropertyPainterPlugin() = default;

    void setPainter(PropertyPainter * painter) { m_painter = painter; }

protected:
    PropertyPainter * painter() const { return m_painter; }

private:
    PropertyPainter * m_painter;
};

template <typename Editor, typename... MoreEditors>
class PropertyPainterPlugin : 
    public PropertyPainterPlugin<Editor>, 
    public PropertyPainterPlugin<MoreEditors...>
{
};

template <typename Editor>
class PropertyPainterPlugin<Editor> : 
    public reflectionzeug::Visitor<typename Editor::Type>,
    public virtual AbstractPropertyPainterPlugin
{
public:
    virtual void visit(typename Editor::Type * property)
    {
        auto painter = this->painter();
        Editor::paint(painter->painter(), painter->option(), *property);
        painter->setDrawn();
    }
};

} // namespace propertyguizeug
