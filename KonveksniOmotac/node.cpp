#include "node.h"
#include "graphview.h"

Node::Node(QColor boja)
{
    this->boja = boja;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QBrush b;
    QPen p;
    b.setStyle(Qt::SolidPattern);
    p.setColor(boja);

    painter->setBrush(b);
    painter->setPen(p);
    painter->drawEllipse(-4, -4, 7, 7);
}

QRectF Node::boundingRect() const
{
    return QRect(-12, -12, 25, 25);
}

QPainterPath Node::shape() const
{
    QPainterPath p;
    p.addEllipse(-10,-10, 20, 20);
    return p;
}

void Node::addEdge(Edge *e)
{
    edges << e;
    e->adjust();
}

qreal Node::x() const
{
    return xPos;
}

qreal Node::y() const
{
    return yPos;
}

QString Node::getColor()
{
    return "black";
}

void Node::setX(int x)
{
    xPos = x;
}

void Node::setY(int y)
{
    yPos = y;
}
