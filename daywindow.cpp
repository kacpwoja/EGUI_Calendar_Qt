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
    auto eventList = EventDB.getEvents(_date);
    if(!eventList)
        return;
    for (auto i = eventList->begin(); i != eventList->end(); ++i )
    {
        QString str = i->timeStart().toString() + " - " + i->timeEnd().toString() + " " + i->title() + " at " + i->location();
        QLabel* lbl = new QLabel;
        lbl->setText(str);
        eventLabels.append(lbl);
        ui->eventsLayout->addWidget(lbl);
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
        eventText = QString(events);

    ui->topbarLabel->setText(eventText + " event" + pluralSuffix + " " + dateText + ".");
}

void DayWindow::newEvent()
{
    EventWindow* eventWin = new EventWindow(_date, this);
    eventWin->exec();
}
