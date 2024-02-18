#ifndef EDITABLE_H
#define EDITABLE_H

#include <QItemDelegate>

class EditableDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    EditableDelegate(QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // EDITABLE_H
