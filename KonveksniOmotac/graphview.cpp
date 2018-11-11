#include "graphview.h"
#include <QPalette>

GraphView::GraphView(QWidget *parent)
    :QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    scenaX = 800;
    scenaY = 600;
    scene->setSceneRect(0, 0, scenaX, scenaY);
    setScene(scene);

    setMinimumSize(500, 500);
    setRenderHint(QPainter::Antialiasing);
}

bool GraphView::nodesEmpty()
{
    return nodes.isEmpty();
}

void GraphView::clearNodes()
{
    scene->clear();
    nodes.clear();
}

QGraphicsScene* GraphView::getScene()
{
    return scene;
}

QVector<Node*> GraphView::getNodes()
{
    return nodes;
}

void GraphView::removeItem(QGraphicsItem* item)
{
    if (scene->items().contains(item))
        scene->removeItem(item);
}

void GraphView::addItem(QGraphicsItem* item)
{
    if (!scene->items().contains(item))
        scene->addItem(item);
}

void GraphView::mousePressEvent(QMouseEvent * event)
{
    newPos = event->pos();
    newPos.setX(newPos.x() - 202);
    newPos.setY(newPos.y() - 12);
}

void GraphView::mouseReleaseEvent(QMouseEvent * event)
{
    /* Provera da li je tacka u prozoru za iscrtavanje */
    if ((newPos.rx() < 3) ||(newPos.rx() > scenaX-3) || (newPos.ry() > scenaY-3) || (newPos.ry() < 3))
        return;

    /* Dodajemo kliknutu tacku u vektor tacaka, i iscrtavamo je */
    Node* n = new Node(Qt::black);
    nodes.append(n);
    scene->addItem(n);
    n->setX(newPos.rx());
    n->setY(newPos.ry());
    n->setPos(n->x(), n->y());
}

void GraphView::drawBackground(QPainter *painter, const QRectF &rect1)
{
    Q_UNUSED(rect1);
    QRectF rect = this->sceneRect();

    painter->drawRect(rect);

    qreal x1, y1, x2, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);
    QLinearGradient lg(x1, y1, x2, y2);

    lg.setColorAt(0.0, QColor(82, 179, 217));
    lg.setColorAt(1, QColor(68, 108, 179));

    painter->fillRect(rect, lg);
}

void GraphView::nacrtajRandomTacke(int brojTacaka)
{
    /* Izbacivanje prethodno nacrtanih elemenata */
    scene->clear();
    nodes.clear();

    for (int i = 0; i < brojTacaka; i++) {
        int x = ((qrand() % ((scenaX-10 + 1) - 10)) + 10);
        int y = ((qrand() % ((scenaY-10 + 1) - 10)) + 10);
        Node* n = new Node(Qt::black);
        nodes.append(n);
        scene->addItem(n);
        n->setX(x);
        n->setY(y);
        n->setPos(n->x(), n->y());
    }
}

bool lessThan(int p1, int p2)
{
    return p1 < p2;
}

void GraphView::nacrtajTackeIzFajla(QString tekst)
{
    QVector<int> xVector, yVector;
    float xScale = 1.0, yScale = 1.0;

    /* Parsiranje tacaka iz teksta fajla */
    QStringList tekstRedovi = tekst.split(QRegExp("\n"));

    /* Skaliranje tacaka tako da stanu u prozor */
    foreach (QString s, tekstRedovi)
    {
        QStringList s1 = s.split(QRegExp(", "));
        int x = s1[0].toInt();
        int y = s1[1].toInt();
        xVector.append(x);
        yVector.append(y);
    }

    std::sort(xVector.begin(), xVector.end(), lessThan);
    std::sort(yVector.begin(), yVector.end(), lessThan);
    int* xMax = std::max_element(xVector.begin(), xVector.end());
    int* yMax = std::max_element(yVector.begin(), yVector.end());

    if (*xMax > scenaX)
        xScale = (scenaX-10)*1.0/(*xMax);
    if (*yMax > scenaY)
        yScale = (scenaY-10)*1.0/(*yMax);

    foreach (QString s, tekstRedovi)
    {
        QStringList s1 = s.split(QRegExp(", "));
        float x = s1[0].toInt() * xScale;
        float y = s1[1].toInt() * yScale;
        Node* n = new Node(Qt::black);
        nodes.append(n);
        scene->addItem(n);
        n->setX(x);
        n->setY(y);
        n->setPos(n->x(), n->y());
    }

    /* Crtanje tacaka */
    foreach (Node* n, nodes)
    {
        if (!scene->items().contains(n))
            scene->addItem(n);
    }
}
