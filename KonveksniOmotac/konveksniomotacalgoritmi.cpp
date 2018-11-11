#include "konveksniomotacalgoritmi.h"
#include <QtAlgorithms>
#include <QTime>
#include <QStringList>
#include <QCoreApplication>

Node* P1;

konveksniomotacalgoritmi::konveksniomotacalgoritmi(QObject *parent, GraphView *graphView) : QObject(parent)
{
    this->graphView = graphView;
}

void konveksniomotacalgoritmi::setBrzinaAnimacije(int value)
{
    this->brzinaAnimacije = value;
}

void konveksniomotacalgoritmi::clearAll()
{
    graphView->getScene()->clear();
    graphView->clearNodes();
}

QGraphicsScene* konveksniomotacalgoritmi::getScene()
{
    return graphView->getScene();
}

void konveksniomotacalgoritmi::delay()
{
    QTime dieTime = QTime::currentTime().addMSecs(brzinaAnimacije);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void konveksniomotacalgoritmi::pause()
{
    paused = true;
}

void konveksniomotacalgoritmi::unpause()
{
    paused = false;
}

void konveksniomotacalgoritmi::stop()
{
    naiveStopped = true;
    grahamStopped = true;

    /* Izbacivanje grana (i zelenih cvorova u slucaju gremovog algoritma) iz scene */
    foreach(QGraphicsItem *item, graphView->getScene()->items())
    {
        if (!graphView->getNodes().contains((Node*)item))
            removeItem((Node*)item);
    }
}

bool yLessThan(const Node* p1, const Node* p2)
{
    return p1->y() > p2->y();
}

bool xLessThan(const Node* p1, const Node* p2)
{
    if (p1->x() != p2->x())
        return p1->x() > p2->x();
    else
        return yLessThan(p1, p2);
}

bool xAxisLessThan(const Node* p1, const Node* p2)
{
    QLineF prvaLinija, drugaLinija, xOsa;
    QPoint prvaTacka = QPoint(p1->x(), p1->y());
    QPoint drugaTacka = QPoint(p2->x(), p2->y());
    QPoint P11 = QPoint(P1->x(), P1->y());
    QPoint P12 = QPoint(P1->x() + 790, P1->y());
    xOsa.setPoints(P11, P12);

    prvaLinija.setPoints(P11, prvaTacka);
    drugaLinija.setPoints(P11, drugaTacka);

    return prvaLinija.angleTo(xOsa) > drugaLinija.angleTo(xOsa);
}

void konveksniomotacalgoritmi::naivniAlgoritam(int brzinaAnimacije)
{
    QVector<Node*> nodes = graphView->getNodes();
    naiveStopped = false, paused = false;

    /* Povezivanje signal-a i slot-ova */
    QObject::connect(this, SIGNAL(removeItem(QGraphicsItem*)), graphView, SLOT(removeItem(QGraphicsItem*)));
    QObject::connect(this, SIGNAL(addItem(QGraphicsItem*)), graphView, SLOT(addItem(QGraphicsItem*)));

    /* Izbacivanje grana koje su iscrtane prilikom prethodnog pokretanja algoritma,
       dok cvorove ostavljamo */
    foreach(QGraphicsItem *item, graphView->getScene()->items())
    {
        if (!nodes.contains((Node*)item))
            removeItem(item);
    }

    bool valid = false;
    this->brzinaAnimacije = brzinaAnimacije;

    /* Promena oznaka tacaka */
    std::sort(nodes.begin(), nodes.end(), xLessThan);

    for (int i = 0; i < nodes.length(); i++)
    {
        if (naiveStopped)
            return;

        for (int j = 0; j < nodes.length(); j++)
        {
            if (naiveStopped)
                return;

            if (i != j)
                valid = true;

            for (int k = 0; k < nodes.length(); k++)
            {
                if (naiveStopped)
                    return;

                if (k == i || k == j || i == j)
                    continue;

                QLineF prvaLinija, drugaLinija;
                QPoint prvaTacka = QPoint(nodes[i]->x(), nodes[i]->y());
                QPoint drugaTacka = QPoint(nodes[j]->x(), nodes[j]->y());
                QPoint trecaTacka = QPoint(nodes[k]->x(), nodes[k]->y());
                prvaLinija.setPoints(prvaTacka, drugaTacka);
                drugaLinija.setPoints(drugaTacka, trecaTacka);

                /* Ako grana ne ulazi u omotac crtamo je crvenom bojom, a nakon toga je brisemo */
                qreal ugao = prvaLinija.angleTo(drugaLinija);
                if (ugao > 180.0)
                {
                    valid = false;
                    Edge* e1 = new Edge(nodes[i], nodes[j], Qt::red);
                    Edge* e2 = new Edge(nodes[j], nodes[k], Qt::red);
                    addItem(e1);
                    addItem(e2);
                    delay();
                    graphView->update();

                    while (paused)
                    {
                        delay();
                        if (!paused)
                            continue;
                    }

                    removeItem(e1);
                    removeItem(e2);
                }
            }

            /* Ako grana ulazi u omotac crtamo je zelenom bojom */
            if (valid)
            {
                Edge* e = new Edge(nodes[i], nodes[j], Qt::green);
                addItem(e);
                delay();
                graphView->update();
            }
        }
    }
}

void konveksniomotacalgoritmi::prostMnogougao(QVector<Node*>& P)
{
    /* Promena oznaka tacaka */
    std::sort(P.begin(), P.end(), xLessThan);

    /* Sortiranje po uglu koji zaklapaju sa x-osom */
    P1 = P[0];
    std::sort(std::next(P.begin(), 1), P.end(), xAxisLessThan);
}

void konveksniomotacalgoritmi::gremovAlgoritam(int brzinaAnimacije)
{
    QVector<Node*> nodes = graphView->getNodes();
    grahamStopped = false, paused = false;

    /* Povezivanje signal-a i slot-ova */
    connect(this, SIGNAL(removeItem(QGraphicsItem*)), graphView, SLOT(removeItem(QGraphicsItem*)));
    connect(this, SIGNAL(addItem(QGraphicsItem*)), graphView, SLOT(addItem(QGraphicsItem*)));

    /* Izbacivanje grana koje su iscrtane prilikom prethodnog pokretanja algoritma,
       dok cvorove ostavljamo */
    foreach(QGraphicsItem *item, graphView->getScene()->items())
    {
        if (!nodes.contains((Node*)item))
            removeItem((Node*)item);
    }

    QVector<Node*> P;
    QVector<Node*> Q;
    int m = 2;
    bool valid;
    this->brzinaAnimacije = brzinaAnimacije;

    for (int i = 0; i < nodes.length(); i++)
        P.append(nodes[i]);

    prostMnogougao(P);

    /* Dodavanje prve dve tacke u rezultujuci skup tacaka */
    Node* n1 = new Node(Qt::green);
    n1->setPos(P[0]->x(), P[0]->y());
    addItem(n1);
    Node* n2 = new Node(Qt::green);
    n2->setPos(P[1]->x(), P[1]->y());
    addItem(n2);
    Q.append(P[0]);
    Q.append(P[1]);
    Q.append(P[2]);

    for (int k = 3; k < nodes.length(); k++)
    {
        QLineF prvaLinija, drugaLinija;
        QPoint prvaTacka, drugaTacka, trecaTacka;
        Node* n1, *n2, *n3;
        Edge* e1, *e2;
        qreal ugao;

        valid = false;

        while (!valid)
        {
            prvaTacka = QPoint(Q[m-1]->x(), Q[m-1]->y());
            drugaTacka = QPoint(Q[m]->x(), Q[m]->y());
            trecaTacka = QPoint(P[k]->x(), P[k]->y());
            prvaLinija.setPoints(prvaTacka, drugaTacka);
            drugaLinija.setPoints(drugaTacka, trecaTacka);
            ugao = prvaLinija.angleTo(drugaLinija);

            /* Ako grana ne ulazi u omotac srednju od 3 trenutne tacke crtamo crnom bojom
               odnosno izbacujemo je iz omotaca ako je bila ubacena (zelena) */
            if (ugao > 180.0)
            {
                n1 = new Node(Qt::black);
                n2 = new Node(Qt::black);
                n3 = new Node(Qt::black);
                n1->setPos(prvaTacka.x(), prvaTacka.y());
                n2->setPos(drugaTacka.x(), drugaTacka.y());
                n3->setPos(trecaTacka.x(), trecaTacka.y());
                e1 = new Edge(n1, n2, Qt::red);
                e2 = new Edge(n2, n3, Qt::red);

                addItem(e1);
                addItem(e2);
                addItem(n2);
                delay();
                graphView->update();

                if (grahamStopped)
                    return;
                while (paused)
                {
                    delay();
                    if (!paused)
                        continue;
                }

                removeItem(e1);
                removeItem(e2);

                m--;
            }
            else
                valid = true;
        }

        /* Ako grana ulazi u omotac srednju od 3 trenutne tacke crtamo zelenom bojom */
        n1 = new Node(Qt::black);
        n2 = new Node(Qt::green);
        n3 = new Node(Qt::black);
        n1->setPos(prvaTacka.x(), prvaTacka.y());
        n2->setPos(drugaTacka.x(), drugaTacka.y());
        n3->setPos(trecaTacka.x(), trecaTacka.y());
        e1 = new Edge(n1, n2, Qt::green);
        e2 = new Edge(n2, n3, Qt::green);

        addItem(e1);
        addItem(e2);
        addItem(n2);
        delay();
        graphView->update();

        if (grahamStopped)
            return;
        while (paused)
        {
            delay();
            if (!paused)
                continue;
        }

        removeItem(e1);
        removeItem(e2);

        m++;

        /* Dodavanje nove tacke u rezultujuci skup tacaka */
        if (m == Q.length())
            Q.append(P[k]);
        else
            Q[m] = P[k];
    }

    /* Dodavanje poslednje tacke u rezultujuci skup */
    Q[m] = P[P.length()-1];
    n1 = new Node(Qt::green);
    n1->setPos(Q[m]->x(), Q[m]->y());
    addItem(n1);

    /* Crtanje poligona od rezultujucih tacaka */
    for (int i = 1; i < m+1; i++)
    {
        Edge* e = new Edge(Q[i-1], Q[i], Qt::green);
        addItem(e);
        delay();
        graphView->update();
    }

    /* Crtanje poslednje grane */
    Edge* e = new Edge(P[0], P[P.length()-1], Qt::green);
    addItem(e);
}
