#include "daywindow.h"
#include "ui_daywindow.h"
#include "mainwindow.h"
#include <QDate>
#include <QMultiMap>
#include "event.h"
#include "eventwindow.h"
#include "eventbase.h"

DayWindow::DayWindow(const QDate& date, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DayWindow)
{
    ui->setupUi(this);
    _date = date;
    setWindowTitle(_date.toString("dddd, d MMMM yyyy"));
    loadEvents();

    connect(ui->newEventButton, &QPushButton::released, this, &DayWindow::newEvent);
    connect(&EventDB, &EventBase::baseUpdated, this, &DayWindow::loadEvents);
}

DayWindow::~DayWindow()
{
    delete ui;
    QLabel* lbl;
    foreach (lbl, eventLabels)
        delete lbl;
}

void DayWindow::loadEvents()
{
    updateTopText();
    QLabel* lbl;
    foreach (lbl, eventLabels)
    {
        ui->eventsLayout->removeWidget(lbl);
        delete lbl;
    }
    eventLabels.clear();

    auto eventList = EventDB.getEvents(_date);
    if(!eventList)
        return;
    Event ev;
    foreach (ev, *eventList)
    {
        QString str = ev.timeStart().toString("h:mm") + " - " + ev.timeEnd().toString("h:mm") + " " + ev.title();
        if(ev.location() != "")
            str += " at " + ev.location();
        QLabel* lbl = new QLabel;
        lbl->setText(str);
        eventLabels.append(lbl);
        ui->eventsLayout->insertWidget(ui->eventsLayout->count()-1, lbl);
    }
}

void DayWindow::updateTopText()
{
    QString dateText;
    QString pluralSuffix = "";
    QString eventText;
    // Getting date
    if(_date == QDate::currentDate())
        dateText = "today";
    else
        dateText = "on " + _date.toString("ddd d MM yyyy");

    // Getting event count
    int events = EventDB.count(_date);
    if(events != 1)
        pluralSuffix = "s";
    if(events == 0)
        eventText = "No";
    else
        eventText = QString::number(events);

    ui->topbarLabel->setText(eventText + " event" + pluralSuffix + " " + dateText + ".");
}

void DayWindow::newEvent()
{
    EventWindow* eventWin = new EventWindow(_date, this);
    eventWin->exec();
}
