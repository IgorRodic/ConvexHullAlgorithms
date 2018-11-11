#ifndef KONVEKSNIOMOTACALGORITMI_H
#define KONVEKSNIOMOTACALGORITMI_H

#include <QObject>
#include "graphview.h"

class konveksniomotacalgoritmi : public QObject
{
    Q_OBJECT
public:
    explicit konveksniomotacalgoritmi(QObject *parent = 0, GraphView *graphView = 0);

    void naivniAlgoritam(int brzinaAnimacije);
    void gremovAlgoritam(int brzinaAnimacije);

    QGraphicsScene* getScene();
    void setBrzinaAnimacije(int value);
    void clearAll();
    void stop();
    void pause();
    void unpause();

signals:
    void removeItem(QGraphicsItem* item);
    void addItem(QGraphicsItem* item);

private:
    GraphView* graphView;
    int brzinaAnimacije;
    bool naiveStopped;
    bool grahamStopped;
    bool paused;

    void prostMnogougao(QVector<Node*> &P);
    void delay();
};

#endif // KONVEKSNIOMOTACALGORITMI_H
