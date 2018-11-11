#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QList>
#include "edge.h"

#define NODE 200

class GraphView;

class Node : public QGraphicsItem
{
public:
    Node(QColor boja);

    void addEdge(Edge* e);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    qreal x() const;
    qreal y() const;
    QString getColor();

    void setX(int x);
    void setY(int y);

private:
    QList<Edge*> edges;
    GraphView* graph;
    QPointF newPos;
    QColor boja;
    qreal xPos;
    qreal yPos;
};

#endif // NODE_H
