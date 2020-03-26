#ifndef DAYWINDOW_H
#define DAYWINDOW_H

#include <QDialog>
#include <QDate>
#include <QVector>
#include <QLabel>

namespace Ui {
class DayWindow;
}

class DayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DayWindow(QWidget *parent = nullptr);
    ~DayWindow();

    void date(const QDate& date);

private:
    Ui::DayWindow *ui;
    QDate _date;
    QVector<QLabel*> eventLabels;
    void loadEvents();
    void updateTopText();
};

#endif // DAYWINDOW_H
