#include <propertyguizeug/BoolEditor.h>

#include <QApplication>
#include <QCheckBox>
#include <QStyleOptionButton>
#include <QStyleOptionViewItem>

#include <reflectionzeug/Property.h>

using namespace reflectionzeug;
namespace propertyguizeug
{

void BoolEditor::paint(
    QPainter * painter,
    const QStyleOptionViewItem & option,
    Property<bool> & property)
{
    auto opt = QStyleOptionButton{};
    opt.state = property.value() ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    opt.rect = option.rect;
    opt.rect.setLeft(opt.rect.left()/* + PropertyEditor::s_horizontalMargin */);

    auto widget = option.widget;
    auto style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_CheckBox, &opt, painter, widget);
}

BoolEditor::BoolEditor(Property<bool> * property, QWidget * parent)
:   PropertyEditor{parent}
,   m_property{property}
{
    auto checkBox = new QCheckBox{this};

    m_property->toggleValue();

    addWidget(checkBox);
    setFocusProxy(checkBox);

    checkBox->setFocusPolicy(Qt::StrongFocus);
    checkBox->setCheckState(property->value() ? Qt::Checked : Qt::Unchecked);

    connect(checkBox, &QCheckBox::stateChanged,
        [this](int state)
        {
            m_property->setValue(state == Qt::Checked);
        });
    m_propertyChangedConnection = m_property->valueChanged.connect(
        [this, checkBox](bool newValue)
        {
            checkBox->setCheckState(newValue ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
        });
}

BoolEditor::~BoolEditor()
{
    m_propertyChangedConnection.disconnect();
}

} // namespace propertyguizeug
