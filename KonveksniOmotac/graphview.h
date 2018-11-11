#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QWheelEvent>
#include <QGraphicsItem>
#include <QVector>
#include <qmath.h>
#include "node.h"

class GraphView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphView(QWidget *parent = 0);
    void nacrtajRandomTacke(int brojTacaka = 0);
    void nacrtajTackeIzFajla(QString tekst = "");

    bool nodesEmpty();
    void clearNodes();

    QGraphicsScene* getScene();
    QVector<Node*> getNodes();

public slots:
    void removeItem(QGraphicsItem* item);
    void addItem(QGraphicsItem* item);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QGraphicsScene* scene;
    QVector<Node*> nodes;
    QPoint newPos;
    int scenaX;
    int scenaY;
};

#endif // GRAPHVIEW_H
