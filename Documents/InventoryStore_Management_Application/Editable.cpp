#include "Editable.h"
#include <QLineEdit>

EditableDelegate::EditableDelegate(QObject* parent) : QItemDelegate(parent) {}

QWidget* EditableDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // Allow editing only for specific columns (e.g., column 2)
    if (index.column() == 2) {
        QLineEdit* editor = new QLineEdit(parent);
        return editor;
    }
    return QItemDelegate::createEditor(parent, option, index);
}
