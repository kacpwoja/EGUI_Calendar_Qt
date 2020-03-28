#include "daywindow.h"
#include "ui_daywindow.h"
#include "mainwindow.h"
#include <QDate>
#include <QMultiMap>
#include <QLabel>
#include <QHBoxLayout>
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
    EventBox* evbox;
    foreach (evbox, events)
        delete evbox;
}

void DayWindow::loadEvents()
{
    updateTopText();
    // Clear event list
    EventBox* evbox;
    foreach (evbox, events)
    {
        ui->eventsLayout->removeWidget(evbox);
        delete evbox;
    }
    events.clear();

    // Get events from this day
    auto eventList = EventDB.getEvents(_date);
    // No events this day
    if(!eventList)
        return;

    // Add widgets for each event
    Event ev;
    foreach (ev, *eventList)
    {
        EventBox* evbox = new EventBox(ev, this);
        events.append(evbox);
        ui->eventsLayout->insertWidget(ui->eventsLayout->count()-1, evbox);
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
