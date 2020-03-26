#include "eventbox.h"
#include "ui_eventbox.h"
#include "event.h"
#include "eventbase.h"
#include "eventwindow.h"

EventBox::EventBox(const Event& event, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventBox)
{
    ui->setupUi(this);
    _event = event;
    QString str = _event.timeStart().toString("h:mm") + " - " + _event.timeEnd().toString("h:mm") + " " + _event.title();
    if(_event.location() != "")
        str += " at " + _event.location();
    ui->label->setText(str);

    connect(ui->editButton, &QPushButton::released, this, &EventBox::editEvent);
    connect(ui->deleteButton, &QPushButton::released, this, &EventBox::removeEvent);
}

EventBox::~EventBox()
{
    delete ui;
}

void EventBox::editEvent()
{
    EventWindow* eventWin = new EventWindow(_event, parentWidget());
    eventWin->exec();
}

void EventBox::removeEvent()
{
    EventDB.remove(_event);
}

QSize EventBox::sizeHint() const
{
    return QSize(100, 35);
}
