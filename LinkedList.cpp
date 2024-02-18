#include"LinkedList.h"
Node ::Node()
{
    data = nullptr;
    item = nullptr;
}
void Node::set_NewNode(QTableWidgetItem * newitem)
{
    item = newitem;
}
QTableWidgetItem * Node::get_NextNode()
{
    return item;
}
void Node::set_Data(QString * s)
{
    data = s;
}
QString * Node::get_Data()
{
    return data;
}
List::List()
{
    headNode = new Node();
    headNode->set_NewNode(nullptr);
    lastCurrentNode = nullptr;
    currentNode = nullptr;
    size =0;
}
void List::add_Object(QString string)
{
    Node * newNode = new Node();
    newNode->set_Data(&string);
    if(currentNode!=NULL)
    {
        newNode->set_NewNode(currentNode->get_NextNode());
        currentNode->set_NewNode(newNode);
        lastCurrentNode = currentNode;
        currentNode = newNode;
    }
    else
    {
        headNode->set_NewNode(newNode);

    }
}
