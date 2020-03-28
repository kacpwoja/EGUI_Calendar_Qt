#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCalendarWidget>
#include <QTextCharFormat>
#include <QVector>
#include <QFile>
#include <QJsonDocument>
#include "daywindow.h"
#include "eventwindow.h"
#include "eventbase.h"

#define FILENAME "events.json"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //READ FROM FILE
    QFile loadFile(QStringLiteral(FILENAME));
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("File was not read.");
        EventDB.clear();
    }
    else
    {
        QJsonDocument doc = QJsonDocument::fromJson(loadFile.readAll());
        EventDB.read(doc.object());
    }
    loadFile.close();

    formatCalendar();

    connect(ui->todayButton, &QPushButton::released, this, &MainWindow::selectToday);
    connect(ui->newEventButton, &QPushButton::released, this, &MainWindow::newEvent);
    connect(ui->calendar, &QCalendarWidget::selectionChanged, this, &MainWindow::updateTopText);
    connect(ui->calendar, &QCalendarWidget::activated, this, &MainWindow::viewDay);
    connect(&EventDB, &EventBase::baseUpdated, this, &MainWindow::formatCalendar);
    connect(ui->calendar, &QCalendarWidget::currentPageChanged, this, &MainWindow::formatCalendar);
}

MainWindow::~MainWindow()
{
    //SAVE TO FILE
    QFile saveFile(QStringLiteral(FILENAME));
    if(!saveFile.open(QIODevice::WriteOnly))
        qWarning("File was not saved.");
    QJsonObject obj;
    EventDB.write(obj);
    QJsonDocument doc(obj);
    saveFile.write(doc.toJson());
    saveFile.close();

    delete ui;
}

void MainWindow::selectToday()
{
    ui->calendar->setSelectedDate(QDate::currentDate());
}

void MainWindow::formatCalendar()
{
    updateTopText();

    // Reset format for all days
    ui->calendar->setDateTextFormat(QDate(), QTextCharFormat());

    // Format for event days
    QTextCharFormat eventFormat;
    auto palette = qApp->palette();
    eventFormat.setBackground(palette.brush(QPalette::Mid));

    // Setting format for all event days
    QDate it = QDate(ui->calendar->yearShown(), ui->calendar->monthShown(), 1);
    while(it.month() == ui->calendar->monthShown())
    {
        if(EventDB.count(it) > 0)
        {
            ui->calendar->setDateTextFormat(it, eventFormat);
        }
        it = it.addDays(1);
    }

}

void MainWindow::updateTopText()
{
    QString dateText;
    QString pluralSuffix = "";
    QString eventText;
    // Getting date
    if(ui->calendar->selectedDate() == QDate::currentDate())
        dateText = "today";
    else
        dateText = "on " + ui->calendar->selectedDate().toString("d MMMM yyyy");

    // Getting event count
    int events = EventDB.count(ui->calendar->selectedDate());
    if(events != 1)
        pluralSuffix = "s";
    if(events == 0)
        eventText = "no";
    else
        eventText = QString::number(events);

    ui->dayEventsLabel->setText("You have " + eventText + " event" + pluralSuffix + " " + dateText + ".");
}

void MainWindow::viewDay(const QDate& date)
{
    DayWindow* dayWin = new DayWindow(date, this);
    dayWin->exec();
}

void MainWindow::newEvent()
{
    EventWindow* eventWin = new EventWindow(ui->calendar->selectedDate(), this);
    eventWin->exec();
}
