
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <propertyguizeug/FilePathEditor.h>

namespace propertyguizeug {
    
FilePathEditor::FilePathEditor(Property<FilePath> * property, QWidget * parent)
:   QWidget(parent)
,   m_layout(new QHBoxLayout(this))
,   m_property(property)
{
    m_layout->setMargin(0);
    m_layout->setContentsMargins(0, 0, 0, 0);

    QLineEdit * lineEdit = new QLineEdit(this);
    lineEdit->setText(QString::fromStdString(m_property->value().string()));
    QPushButton * button = new QPushButton("…", this);

    m_layout->addWidget(lineEdit);
    m_layout->addWidget(button);
}

FilePathEditor::~FilePathEditor()
{
}
    
} // namespace
