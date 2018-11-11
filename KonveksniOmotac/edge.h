#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
public:
    Edge(Node* s, Node* d, QColor boja);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void adjust();

    Node *sourceNode() const;
    Node *destNode() const;
    Node* source;
    Node* dest;
    QColor boja;

private:
    QPointF sourcePoint;
    QPointF destPoint;
};

#endif // EDGE_H
