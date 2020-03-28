#include "eventwindow.h"
#include "ui_eventwindow.h"
#include <QMessageBox>
#include "event.h"
#include "eventbase.h"

EventWindow::EventWindow(const QDate& date, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(date);
    ui->tStartEdit->setTime(QTime::currentTime());
    ui->tEndEdit->setTime(QTime(QTime::currentTime().hour()+1,QTime::currentTime().minute()));
    ui->titleEdit->setPlainText("Event");
    edit = false;
    this->setWindowTitle("New Event");
}

EventWindow::EventWindow(const Event& event, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(event.date());
    ui->tStartEdit->setTime(event.timeStart());
    ui->tEndEdit->setTime(event.timeEnd());
    ui->titleEdit->setPlainText(event.title());
    ui->locationEdit->setPlainText(event.location());
    edit = true;
    old_event = event;
    this->setWindowTitle("Edit Event");
}

EventWindow::~EventWindow()
{
    delete ui;
}

void EventWindow::accept()
{
    try
    {
        Event ev(ui->dateEdit->date(), ui->tStartEdit->time(), ui->tEndEdit->time(), ui->titleEdit->toPlainText(), ui->locationEdit->toPlainText());
        if(edit)
            EventDB.remove(old_event);
        EventDB.add(ev);
    }
    catch (Event::EventException& e)
    {
        QMessageBox* errmsg = new QMessageBox(this);
        errmsg->setText("Events can't end before they start!");
        errmsg->setWindowTitle("Error!");
        errmsg->exec();
        return;
    }
    QDialog::accept();
}
