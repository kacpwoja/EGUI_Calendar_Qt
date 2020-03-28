#ifndef DAYWINDOW_H
#define DAYWINDOW_H

#include <QDialog>
#include <QDate>
#include <QVector>
#include "eventbox.h"

namespace Ui {
class DayWindow;
}

class DayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DayWindow(const QDate& date, QWidget *parent = nullptr);
    ~DayWindow();

    void date(const QDate& date);

private:
    Ui::DayWindow *ui;
    QDate _date;
    QVector<EventBox*> events;

private slots:
    void loadEvents();
    void updateTopText();
    void newEvent();
};

#endif // DAYWINDOW_H
