#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "graphview.h"
#include "konveksniomotacalgoritmi.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_naivniAlgoritam_clicked();
    void on_gremovAlgoritam_clicked();

    void on_ucitavanjeFajla_clicked();

    void on_uputstvo_clicked();

    void on_brzinaAnimacije_valueChanged(int value);

    void on_generisiTacke_clicked();

    void on_obrisiSve_clicked();

    void on_pauzaNastavak_clicked();

    void on_stop_clicked();

private:
    Ui::Widget *ui;
    konveksniomotacalgoritmi* koa;

    void iskljuciDugmice();
    void ukljuciDugmice();
};

#endif // WIDGET_H
