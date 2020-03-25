#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCalendarWidget>
#include <QTextCharFormat>
#include <QVector>
#include "daywindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    eventList = new QMultiMap<QDate, Event>();
    connect(ui->todayButton, &QPushButton::released, this, &MainWindow::selectToday);
    connect(ui->calendar, &QCalendarWidget::selectionChanged, this, &MainWindow::updateTopText);
    connect(ui->calendar, &QCalendarWidget::activated, this, &MainWindow::viewDay);
    testfun();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testfun()
{
    QTextCharFormat eeeFormat;
    eeeFormat.setBackground(Qt::red);
    QDate date(2020, 3, 10);
    ui->calendar->setDateTextFormat(date, eeeFormat);
}

void MainWindow::selectToday()
{
    ui->calendar->setSelectedDate(QDate::currentDate());
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
    int events = eventList->count(ui->calendar->selectedDate());
    if(events != 1)
        pluralSuffix = "s";
    if(events == 0)
        eventText = "no";
    else
        eventText = QString(events);

    ui->dayEventsLabel->setText("You have " + eventText + " event" + pluralSuffix + " " + dateText);
}

void MainWindow::viewDay(const QDate& date)
{
    DayWindow* dayWin = new DayWindow(this);
    dayWin->date(date);
    dayWin->show();
}
