#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "qtablewidget.h"
class Node
{
    QString * data;
    QTableWidgetItem * item;
public:
    Node();
    void set_NewNode(QTableWidgetItem *);
    QTableWidgetItem * get_NextNode();
    void set_Data(QString *);
    QString * get_Data();
};
class List
{
    int size;
    Node * headNode;
    Node * currentNode;
    Node * lastCurrentNode;
public:
    List();
    void add_Object(QString);
    QString get();
    bool Next();
    QString * Traverse();

};

#endif // LINKEDLIST_H
