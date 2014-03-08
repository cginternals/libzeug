//
//#include <QLineEdit>
//
//#include <reflectionzeug/Property.h>
//
//#include "IntSetEditor.h"
//
//using namespace reflectionzeug;
//namespace propertyguizeug
//{
//    
//IntSetEditor::IntSetEditor(Property<std::set<int>> * property, QWidget * parent)
//:   SetEditor("(-?\\d+)", QString::fromStdString(property->toString()), parent)
//,   m_property(property)
//{
//}
//
//IntSetEditor::~IntSetEditor()
//{   
//}
//    
//void IntSetEditor::setSet()
//{
//    std::set<int> set;
//    this->valuesFromText([&set] (const QString & value) {
//        set.insert(value.toInt());
//    });
//    m_property->setValue(set);
//}
//
//} // namespace propertyguizeug
