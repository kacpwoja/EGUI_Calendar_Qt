#include "daywindow.h"
#include "ui_daywindow.h"

DayWindow::DayWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DayWindow)
{
    ui->setupUi(this);
}

DayWindow::~DayWindow()
{
    delete ui;
}

void DayWindow::date(const QDate& date)
{
    _date = date;
    setWindowTitle(_date.toString("dddd, d MMMM yyyy"));
}
