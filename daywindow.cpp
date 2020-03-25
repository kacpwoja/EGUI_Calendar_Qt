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
