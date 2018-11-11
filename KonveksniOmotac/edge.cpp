#include "edge.h"
#include "node.h"

#include <math.h>
#include <QPainter>

Edge::Edge(Node* s, Node* d, QColor boja)
    :source(s), dest(d)
{
    setZValue(-1);
    source->addEdge(this);
    dest->addEdge(this);
    this->boja = boja;
    adjust();
}

QRectF Edge::boundingRect() const
{
    qreal w = destPoint.x() - sourcePoint.x();
    qreal h = destPoint.y() - sourcePoint.y();

    return QRectF(sourcePoint, QSizeF(w, h)).normalized();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen p;
    p.setWidth(3);
    p.setColor(boja);
    painter->setPen(p);
    painter->drawLine(sourcePoint, destPoint);
}

void Edge::adjust()
{
    prepareGeometryChange();

    sourcePoint = source->pos();
    destPoint = dest->pos();
}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}
