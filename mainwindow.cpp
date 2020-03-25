#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCalendarWidget>
#include <QTextCharFormat>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->todayButton, SIGNAL(released()), this, SLOT(selectToday()));
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
