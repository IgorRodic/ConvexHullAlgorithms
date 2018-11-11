#include "widget.h"
#include "ui_widget.h"
#include "konveksniomotacalgoritmi.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    koa = new konveksniomotacalgoritmi(this, this->ui->graphicsView);
    this->ui->pauzaNastavak->setDisabled(true);
    this->ui->stop->setDisabled(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::iskljuciDugmice()
{
    this->ui->generisiTacke->setDisabled(true);
    this->ui->ucitavanjeFajla->setDisabled(true);
    this->ui->naivniAlgoritam->setDisabled(true);
    this->ui->gremovAlgoritam->setDisabled(true);
    this->ui->obrisiSve->setDisabled(true);
    this->ui->pauzaNastavak->setDisabled(false);
    this->ui->stop->setDisabled(false);
}

void Widget::ukljuciDugmice()
{
    this->ui->generisiTacke->setDisabled(false);
    this->ui->ucitavanjeFajla->setDisabled(false);
    this->ui->naivniAlgoritam->setDisabled(false);
    this->ui->gremovAlgoritam->setDisabled(false);
    this->ui->obrisiSve->setDisabled(false);
    this->ui->pauzaNastavak->setDisabled(true);
    this->ui->stop->setDisabled(true);
}

void Widget::on_ucitavanjeFajla_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "All files (*.*);;Text files (*.txt)");
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Greska!", "Fajl nije pronađen!");
        messageBox.setFixedSize(500, 200);
        return;
    }

    QTextStream in(&file);
    QString tekst = in.readAll();
    file.close();

    /* Ciscenje scene i broja unetih tacaka */
    koa->clearAll();
    this->ui->graphicsView->nacrtajTackeIzFajla(tekst);
}

void Widget::on_generisiTacke_clicked()
{
    /* Provera unosa tacaka */
    if (!this->ui->brojTacaka->text().isEmpty())
    {
        int brojTacaka = this->ui->brojTacaka->text().toInt();
        this->ui->graphicsView->nacrtajRandomTacke(brojTacaka);
    }
    else if (!this->ui->graphicsView->nodesEmpty())
    {
        /* Ciscenje broja unetih tacaka */
        this->ui->brojTacaka->clear();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Greska!", "Niste uneli tačke!");
        messageBox.setFixedSize(500, 200);
        return;
    }
}

void Widget::on_naivniAlgoritam_clicked()
{
    if (!koa->getScene()->items().empty())
    {
        /* Onesposobljavanje dugmica */
        iskljuciDugmice();

        int brzinaAnimacije = this->ui->brzinaAnimacije->value();
        koa->naivniAlgoritam(qRound(2000.0/brzinaAnimacije));

        /* Ponovno osposobljavanje dugmica */
        ukljuciDugmice();

        if (this->ui->pauzaNastavak->text() == "Nastavak")
            this->ui->pauzaNastavak->setText("Pauza");
    }
}

void Widget::on_gremovAlgoritam_clicked()
{
    if (!koa->getScene()->items().empty())
    {
        /* Onesposobljavanje dugmica */
        iskljuciDugmice();

        int brzinaAnimacije = this->ui->brzinaAnimacije->value();
        koa->gremovAlgoritam(qRound(2000.0/brzinaAnimacije));

        /* Ponovno osposobljavanje dugmica */
        ukljuciDugmice();

        if (this->ui->pauzaNastavak->text() == "Nastavak")
            this->ui->pauzaNastavak->setText("Pauza");
    }
}

void Widget::on_brzinaAnimacije_valueChanged(int value)
{
    koa->setBrzinaAnimacije(qRound(2000.0/value));
}

void Widget::on_pauzaNastavak_clicked()
{
    if (this->ui->pauzaNastavak->text() == "Pauza")
    {
        koa->pause();
        this->ui->pauzaNastavak->setText("Nastavak");
    }
    else
    {
        koa->unpause();
        this->ui->pauzaNastavak->setText("Pauza");
    }
}

void Widget::on_stop_clicked()
{
    koa->stop();

    if (this->ui->pauzaNastavak->text() == "Pauza")
        this->ui->pauzaNastavak->setText("Nastavak");
    else
        this->ui->pauzaNastavak->setText("Pauza");

    ukljuciDugmice();
}

void Widget::on_obrisiSve_clicked()
{
    koa->clearAll();
}

void Widget::on_uputstvo_clicked()
{
    QMessageBox::information(this, tr("Uputstvo za korišćenje"),
     "Ovo je program za generisanje konveksnog omotača skupa tačaka.\n\n"
     "Za njegovo nalaženje implementirana su dva algoritma:\n"
     "1) Naivni - složenosti O(n^3)\n"
     "2) Gremov - složenosti O(nlogn)\n\n"
     "Postoje 3 načina za unos tačaka:\n"
     "1) Unosi se broj tačaka i pritiskom na dugme 'Generiši slučajne tačke' program generiše pseudo slučajne tačke\n"
     "2) Tačke se učitavaju iz fajla (pritom, format fajla mora da bude takav da se u svakom novom redu unose x i y koordinate tačaka, odvojene zarezom)\n"
     "3) Tačke se unose interaktivno (levim klikom miša na prozor)\n\n"
     "Moguće je izabrati brzinu animacije algoritma, kao i pauzirati algoritam, ili ga stopirati, u bilo kom trenutku izvršavanja programa.\n\n"
     "Dugme 'Obriši sve' služi da se uklone svi elementi iz prozora, sa ciljem započinjanja novog unosa tačaka.");
}
